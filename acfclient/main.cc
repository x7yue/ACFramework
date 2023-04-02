#include <Windows.h>
#include <iostream>
#include <list>

#include "client_window.h"
#include "message_loop_manager.h"

#include "include/acf_environment.h"

AcfRefPtr<AcfEnvironment> g_env;
AcfRefPtr<AcfProfile> g_profile;
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

class TestProfileHandler : public AcfProfileHandler {
 public:
  void OnProfileCreated(AcfRefPtr<AcfProfile> profile) override {
    // dispatch task
    AcfRefPtr<TestTask> task = new TestTask();
    msg_dispatcher->PostTask(task);
  }

  void OnProfileDestroyed(AcfRefPtr<AcfProfile> profile) override {}

  void OnProfileRemoveDataCompleted(AcfRefPtr<AcfProfile> profile,
                                    AcfUserData token) override {
    ::MessageBox(0, L"Clear browsing data done.",
                 L"AcfClient - ClearBrowsingData", MB_ICONINFORMATION);
  }

  IMPLEMENT_REFCOUNTING(TestProfileHandler);
};

class TestEnvHandler : public AcfEnvironmentHandler {
 public:
  TestEnvHandler() { std::cout << "Init Handler\n"; }
  ~TestEnvHandler() override { std::cout << "Quit Handler\n"; }

  void OnEnvironmentInitialized(AcfRefPtr<AcfEnvironment> env) override;

  IMPLEMENT_REFCOUNTING(TestEnvHandler);
};

void TestEnvHandler::OnEnvironmentInitialized(AcfRefPtr<AcfEnvironment> env) {
  std::cout << "[ACF] Browser version: " << env->GetBrowserVersion().c_str() << "\n";

  g_profile = env->CreateProfile("ACFClientProfile", new TestProfileHandler());
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

  // Main loop
  MessageLoopRun();

  g_profile.release();


  // wait for browser process
  std::cout << "[ACFClient] Browser ExitCode: " << g_env->Terminate();
  g_env.release();

  delete msg_dispatcher;

  AcfEnvironment::QuitACFContext();

  return 0;
}
