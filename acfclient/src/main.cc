#include <Windows.h>
#include <iostream>
#include <list>

#include "client_window.h"
#include "message_loop_manager.h"

#include "include/acf_environment.h"

AcfRefPtr<AcfEnvironment> g_env;
acfclient::MessageWindow* msg_dispatcher;

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

  void OnEnvironmentInitialized(AcfRefPtr<AcfEnvironment> env) override;

  IMPLEMENT_REFCOUNTING(TestEnvHandler);
};

void TestEnvHandler::OnEnvironmentInitialized(AcfRefPtr<AcfEnvironment> env) {
  std::cout << "[ACF] Browser version: " << env->GetBrowserVersion().c_str() << "\n";

  AcfRefPtr<TestTask> task = new TestTask();
  msg_dispatcher->PostTask(task);
}

void InitEnv(int argc, char** argv) {
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

int main(int argc, char** argv) {
  ::SetProcessDPIAware();

  AcfEnvironment::InitACFContext();

  msg_dispatcher = new acfclient::MessageWindow(GetModuleHandle(0));

  InitEnv(argc, argv);

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
  std::cout << "[ACFClient] Browser ExitCode: " << g_env->Terminate();
  g_env.release();

  delete msg_dispatcher;

  AcfEnvironment::QuitACFContext();

  return 0;
}
