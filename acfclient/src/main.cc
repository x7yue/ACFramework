#include <Windows.h>
#include <iostream>
#include <list>

#include "client_window.h"
#include "message_loop_manager.h"

#include "include/acf_environment.h"

AcfRefPtr<AcfEnvironment> g_env;
AcfRefPtr<AcfProfile> g_profile;
acfclient::MessageWindow *msg_dispatcher;

class TestTask : public acfclient::Task {
public:
    TestTask() {}

    ~TestTask() override {}

    void Execute() override;

IMPLEMENT_REFCOUNTING(TestTask);
};

void TestTask::Execute() {
    AcfRefPtr<acfclient::Window> window = new acfclient::Window(g_env, GetModuleHandle(0), nullptr);
    window->Show();
}

class TestEnvHandler : public AcfEnvironmentHandler {
public:
    TestEnvHandler() { std::cout << "Init Handler\n"; }

    ~TestEnvHandler() override { std::cout << "Quit Handler\n"; }

    void OnInitialized(AcfRefPtr<AcfEnvironment> env, bool success) override;

IMPLEMENT_REFCOUNTING(TestEnvHandler);
};

void TestEnvHandler::OnInitialized(AcfRefPtr<AcfEnvironment> env, bool success) {
    std::cout << "[ACF] Browser version: " << env->GetBrowserVersion().c_str() << "\n";

    g_profile = env->CreateProfile("TestCPP", nullptr);

    std::cout << "OnInitialized 1\n";
    while (!g_profile->IsValid())
        ::Sleep(0);
    std::cout << "OnInitialized 2\n";

    AcfRefPtr<TestTask> task = new TestTask();
    msg_dispatcher->PostTask(task);
}

void InitEnv(int argc, char **argv) {
    AcfEnvironmentSettings settings;

    if (argc > 2) {
        for (int i = 1; i <= argc - 1; i++) {
            AcfString(&settings.command_line) =
                    AcfString(&settings.command_line).ToString() + argv[i] + " ";
        }
    }

    g_env = AcfEnvironment::CreateEnvironment("chrome.exe", settings,
                                              new TestEnvHandler());
}

void MessageLoopRun() {
    MSG msg;
    // Run the application message loop.
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

int main(int argc, char **argv) {
    // 将进程默认 DPI 感知设置为系统 DPI 感知
    ::SetProcessDPIAware();

    // 初始化ACF
    AcfEnvironment::InitACFContext();

    // 初始化窗口消息处理类（为了进程通讯）GetModuleHandle(0) 获取本进程句柄
    msg_dispatcher = new acfclient::MessageWindow(GetModuleHandle(0));

    InitEnv(argc, argv);

    std::cout << "[ACFClient] Run main loop" << '\n';

    if (!g_env) {
        ::MessageBox(0,
                     L"There is already a ACF browser window running in current "
                     L"user data dir.",
                     L"AcfClient", 0);
        return 0;
    }

    // Main loop
    MessageLoopRun();

    // wait for browser process
    std::cout << "[ACFClient] Browser ExitCode: " << g_env->Terminate() << '\n';

    delete msg_dispatcher;

    AcfEnvironment::QuitACFContext();

    return 0;
}
