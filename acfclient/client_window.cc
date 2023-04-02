
#include "client_window.h"
#include "message_loop_manager.h"

#define IDC_GoBack 201
#define IDC_GoForward 202
#define IDC_Reload 203
#define IDC_Stop 204
#define IDC_Nav 205
#define IDC_More 206

#define IDC_NewWindow 301
#define IDC_CloseWindow 302
#define IDC_ToggleVisible 303
#define IDC_ClearCache 304
#define IDC_EnumFrames 305

extern AcfRefPtr<AcfEnvironment> g_env;
extern AcfRefPtr<AcfProfile> g_profile;
extern acfclient::MessageWindow* msg_dispatcher;

namespace {

class TestTask_Quit : public acfclient::Task {
 public:
  TestTask_Quit() {}
  ~TestTask_Quit() override {}

  void Execute() override;

  IMPLEMENT_REFCOUNTING(TestTask_Quit);
};

void TestTask_Quit::Execute() {
  PostQuitMessage(0);
}

class TestTask_NewWindow : public acfclient::Task {
 public:
  TestTask_NewWindow() {}
  ~TestTask_NewWindow() override {}

  void Execute() override;

  AcfRefPtr<AcfNewWindowDelegate> new_browser_delegate_;
  AcfString url_;

  IMPLEMENT_REFCOUNTING(TestTask_NewWindow);
};

void TestTask_NewWindow::Execute() {
  AcfRefPtr<acfclient::Window> window = new acfclient::Window(
      g_env, GetModuleHandle(0), nullptr, new_browser_delegate_);
  ::SetWindowText(window->GetEditHandle(), (LPCWSTR)url_.ToString16().c_str());
  window->Show();
}

}  // namespace

namespace acfclient {

std::vector<AcfRefPtr<AcfBrowser>> g_browsers;

static const wchar_t kClassName[] = L"acfClient_Window";

WNDPROC SetWndProcPtr(HWND hWnd, WNDPROC wndProc) {
  WNDPROC old =
      reinterpret_cast<WNDPROC>(::GetWindowLongPtr(hWnd, GWLP_WNDPROC));
  [[maybe_unused]] LONG_PTR result = ::SetWindowLongPtr(
      hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(wndProc));
  return old;
}

void SetUserDataPtr(HWND hWnd, void* ptr) {
  SetLastError(ERROR_SUCCESS);
  [[maybe_unused]] LONG_PTR result =
      ::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(ptr));
}

template <typename T>
T GetUserDataPtr(HWND hWnd) {
  return reinterpret_cast<T>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
}

Window::Window(AcfRefPtr<AcfEnvironment> env,
               HINSTANCE instance,
               RECT* initial_rect,
               AcfRefPtr<AcfNewWindowDelegate> new_window)
    : instance_(instance), new_browser_delegate_(new_window) {
  RegisterWindowClass();

  [[maybe_unused]] int x, y, width, height;
  if (!initial_rect || ::IsRectEmpty(initial_rect)) {
    // Use the default window position/size.
    x = y = width = height = CW_USEDEFAULT;
  } else {
    x = initial_rect->left;
    y = initial_rect->top;
    width = initial_rect->right - initial_rect->left;
    height = initial_rect->bottom - initial_rect->top;
  }

  const DWORD dwStyle = WS_OVERLAPPEDWINDOW;
  window_ = CreateWindow(kClassName, L"acfclient", dwStyle, x, y, width, height,
                         nullptr, nullptr, instance, this);
  UpdateWindow(window_);

  // Create browser
  AcfBrowserCreateParams params;
  RECT bound = GetBrowserBound();

  CreateMenu();

  if (IsWindow(window_)) {
    std::cout << "[ACFClient] Window:" << (DWORD)window_ << "\n";
  }

  params.parent = window_;
  params.x = bound.left;
  params.y = bound.top;
  params.width = bound.right;
  params.height = bound.bottom;

  // Call on any thread
  env->CreateBrowser(g_profile, this, params, nullptr);

  std::cout << "Window Create: " << g_browsers.size() << "\n";
}

Window::~Window() {
  std::cout << "Window Destroy: " << g_browsers.size() << "\n";

  if (more_menu_)
    DestroyMenu(more_menu_);

  SetUserDataPtr(window_, nullptr);
  PostMessage(window_, WM_CLOSE, 0, 0);

  if (g_browsers.size() <= 0) {
    msg_dispatcher->PostTask(new TestTask_Quit());
  }
}

void Window::Show() {
  ShowWindow(window_, SW_SHOW);
}

void Window::Hide() {
  ShowWindow(window_, SW_HIDE);
}

HWND Window::GetHandle() {
  return window_;
}

HWND Window::GetHandle() const {
  return window_;
}

LRESULT CALLBACK Window::MainWndProc(HWND hWnd,
                                     UINT message,
                                     WPARAM wParam,
                                     LPARAM lParam) {
  Window* self = nullptr;
  self = GetUserDataPtr<Window*>(hWnd);

  // Callback for the main window
  switch (message) {
    case WM_NCCREATE: {
      CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
      self = reinterpret_cast<Window*>(cs->lpCreateParams);
      SetUserDataPtr(hWnd, self);
      break;
    }
    case WM_CREATE: {
      self->OnCreate(hWnd);
      break;
    }
    case WM_SIZE: {
      if (self)
        self->OnSize(hWnd);
      break;
    }
    case WM_CLOSE:
      // wait for browser
      if (self) {
        self->OnClose();
        return 0;
      } else
        break;
    case WM_SETFOCUS: {
      if (self)
        self->OnFocus();
      break;
    }
    case WM_PAINT: {
      PAINTSTRUCT ps;
      BeginPaint(hWnd, &ps);
      EndPaint(hWnd, &ps);
      break;
    }
    case WM_COMMAND:
      if (self->OnCommand(LOWORD(wParam)))
        return 0;
      break;
    default:
      break;
  }

  return DefWindowProc(hWnd, message, wParam, lParam);
}

void Window::OnClose() {
  if (browser_weak_ptr_ && browser_weak_ptr_->IsValid()) {
    browser_weak_ptr_->Close(false);
  }
}

void Window::OnFocus() {
  if (browser_weak_ptr_ && browser_weak_ptr_->IsValid()) {
    browser_weak_ptr_->Focus();
  }
}

void Window::CreateMenu() {
  more_menu_ = ::CreatePopupMenu();

  MENUITEMINFO info = {0};
  info.cbSize = sizeof(MENUITEMINFO);

  UINT count = 0;

  std::wstring labelStr(L"New Window");
  info.fMask |= MIIM_STRING | MIIM_ID;
  info.cch = labelStr.size();
  info.dwTypeData = const_cast<LPWSTR>(labelStr.c_str());
  info.wID = IDC_NewWindow;
  ::InsertMenuItem(more_menu_, count, TRUE, &info);
  count++;

  labelStr = L"Close Window";
  info.fMask |= MIIM_STRING | MIIM_ID;
  info.cch = labelStr.size();
  info.dwTypeData = const_cast<LPWSTR>(labelStr.c_str());
  info.wID = IDC_CloseWindow;
  ::InsertMenuItem(more_menu_, count, TRUE, &info);
  count++;

  labelStr = L"Toggle Visibility";
  info.fMask |= MIIM_STRING | MIIM_ID;
  info.cch = labelStr.size();
  info.dwTypeData = const_cast<LPWSTR>(labelStr.c_str());
  info.wID = IDC_ToggleVisible;
  ::InsertMenuItem(more_menu_, count, TRUE, &info);
  count++;

  labelStr = L"Clear All BrowsingData";
  info.fMask |= MIIM_STRING | MIIM_ID;
  info.cch = labelStr.size();
  info.dwTypeData = const_cast<LPWSTR>(labelStr.c_str());
  info.wID = IDC_ClearCache;
  ::InsertMenuItem(more_menu_, count, TRUE, &info);
  count++;

  labelStr = L"Enum Frames Info";
  info.fMask |= MIIM_STRING | MIIM_ID;
  info.cch = labelStr.size();
  info.dwTypeData = const_cast<LPWSTR>(labelStr.c_str());
  info.wID = IDC_EnumFrames;
  ::InsertMenuItem(more_menu_, count, TRUE, &info);
  count++;
}

bool Window::OnCommand(UINT id) {
  switch (id) {
    case IDC_GoBack:  // Back button
      if (browser_weak_ptr_)
        browser_weak_ptr_->GoBack();
      break;
    case IDC_GoForward:  // Forward button
      if (browser_weak_ptr_)
        browser_weak_ptr_->GoForward();
      break;
    case IDC_Reload:  // Reload button
      if (browser_weak_ptr_)
        browser_weak_ptr_->Reload(false);
      break;
    case IDC_Stop:  // Stop button
      if (browser_weak_ptr_)
        browser_weak_ptr_->Stop();
      break;
    case IDC_Nav:  // Navigate button
    {
#define MAX_URL_LENGTH 255
      wchar_t strPtr[MAX_URL_LENGTH + 1] = {0};
      *((LPWORD)strPtr) = MAX_URL_LENGTH;
      LRESULT strLen =
          SendMessage(edit_control_, EM_GETLINE, 0, (LPARAM)strPtr);
      if (strLen > 0) {
        strPtr[strLen] = 0;

        browser_weak_ptr_->LoadURL((const char16_t*)strPtr);
      }
#undef MAX_URL_LENGTH
    } break;
    case IDC_More: {
      POINT pt = {0};
      ::GetCursorPos(&pt);

      ::TrackPopupMenu(more_menu_,
                       TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RIGHTBUTTON, pt.x,
                       pt.y, 0, window_, nullptr);
    } break;
    case IDC_NewWindow: {
      std::cout << "Menu: NewWindow\n";

      AcfRefPtr<TestTask_NewWindow> task = new TestTask_NewWindow();
      task->new_browser_delegate_ = nullptr;
      msg_dispatcher->PostTask(task);
    } break;
    case IDC_CloseWindow: {
      std::cout << "Menu: CloseWindow\n";

      PostMessage(window_, WM_CLOSE, 0, 0);
    } break;
    case IDC_ToggleVisible: {
      // toggle visible
      if (browser_weak_ptr_) {
        std::cout << "Menu: Set to Visible: "
                  << !browser_weak_ptr_->GetVisible() << "\n";
        browser_weak_ptr_->SetVisible(!browser_weak_ptr_->GetVisible());
      }
    } break;
    case IDC_ClearCache: {
      g_profile->RemoveBrowsingData(AcfProfile::RemoveDataType::ALL_DATA_TYPES,
                                    true, nullptr);
    } break;
    case IDC_EnumFrames: {
      if (browser_weak_ptr_) {
        std::vector<int64> m_ids;
        browser_weak_ptr_->GetFrameIdentifiers(m_ids);

        for (auto i : m_ids) {
          AcfRefPtr<AcfFrame> f = browser_weak_ptr_->GetFrame(i);

          if (f)
            std::cout << "FrameID: " << f->GetIdentifier()
                      << " Name: " << f->GetName().ToString()
                      << " URL: " << f->GetURL().ToString() << "\n";
        }
      }
    } break;
    default:
      return false;
  }

  // menu command except
  if (id < 300)
    OnFocus();

  return true;
}

void Window::OnCreate(HWND window) {
  RECT rect;
  GetClientRect(window, &rect);

  int x_offset = 0;

  const int button_width = 72;
  const int urlbar_height = 24;

  back_button_ =
      CreateWindow(L"BUTTON", L"Back", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                   x_offset, 0, button_width, urlbar_height, window,
                   reinterpret_cast<HMENU>(IDC_GoBack), instance_, 0);
  x_offset += button_width;

  forward_button_ =
      CreateWindow(L"BUTTON", L"Forward", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                   x_offset, 0, button_width, urlbar_height, window,
                   reinterpret_cast<HMENU>(IDC_GoForward), instance_, 0);
  x_offset += button_width;

  reload_button_ =
      CreateWindow(L"BUTTON", L"Reload", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                   x_offset, 0, button_width, urlbar_height, window,
                   reinterpret_cast<HMENU>(IDC_Reload), instance_, 0);
  x_offset += button_width;

  stop_button_ =
      CreateWindow(L"BUTTON", L"Stop", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                   x_offset, 0, button_width, urlbar_height, window,
                   reinterpret_cast<HMENU>(IDC_Stop), instance_, 0);
  x_offset += button_width;

  more_button_ =
      CreateWindow(L"BUTTON", L"More", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                   x_offset, 0, button_width, urlbar_height, window,
                   reinterpret_cast<HMENU>(IDC_More), instance_, 0);
  x_offset += button_width;

  edit_control_ = CreateWindow(L"EDIT", 0,
                               WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT |
                                   ES_AUTOVSCROLL | ES_AUTOHSCROLL,
                               x_offset, 0, rect.right - button_width * 6,
                               urlbar_height, window, 0, instance_, 0);

  nav_button_ = CreateWindow(
      L"BUTTON", L"Navigate", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
      rect.right - button_width, 0, button_width, urlbar_height, window,
      reinterpret_cast<HMENU>(IDC_Nav), instance_, 0);
}

void Window::OnSize(HWND window) {
  RECT rect;
  GetClientRect(window, &rect);

  const int button_width = 72;
  const int urlbar_height = 24;

  SetWindowPos(edit_control_, 0, button_width * 5, 0,
               rect.right - button_width * 6, urlbar_height, SWP_NOZORDER);
  SetWindowPos(nav_button_, 0, rect.right - button_width, 0, button_width,
               urlbar_height, SWP_NOZORDER);

  if (browser_window_)
    SetWindowPos(browser_window_, 0, 0, urlbar_height, rect.right,
                 rect.bottom - urlbar_height, SWP_NOZORDER);
}

RECT Window::GetBrowserBound() {
  const int urlbar_height = 24;

  RECT rect;
  GetClientRect(window_, &rect);

  return {0, urlbar_height, rect.right, rect.bottom - urlbar_height};
}

void Window::RegisterWindowClass() {
  // Only register the class one time.
  static bool class_registered = false;
  if (class_registered)
    return;
  class_registered = true;

  WNDCLASSEX wcex = {0};

  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.lpszClassName = kClassName;
  wcex.lpfnWndProc = MainWndProc;
  wcex.hInstance = instance_;
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

  RegisterClassEx(&wcex);
}

void Window::SetBrowser(HWND handle) {
  browser_window_ = handle;
  OnSize(window_);
}

// On Brwoser IPC Thread
void Window::OnBrowserCreated(AcfRefPtr<AcfBrowser> browser) {
  std::cout << "OnBrowserCreated\n";

  if (new_browser_delegate_) {
    new_browser_delegate_->SetNewBrowser(browser);
    new_browser_delegate_->HandleRequest(true);
    new_browser_delegate_ = nullptr;
  } else {
    browser->LoadURL("bilibili.com");
  }

  // storage weak ptr
  browser_weak_ptr_ = browser.get();
  SetBrowser(browser->GetWindowHandle());
  Show();

  g_browsers.push_back(browser);
  std::cout << "Append browser\n";
}

void Window::OnNewWindowRequest(AcfRefPtr<AcfBrowser> browser,
                                NewWindowSource source,
                                NewWindowDisposition disposition,
                                bool user_gesture,
                                AcfRefPtr<AcfNewWindowDelegate> delegate) {
  std::cout << "OnNewWindow Request\n";

  AcfRefPtr<TestTask_NewWindow> task = new TestTask_NewWindow();
  task->new_browser_delegate_ = delegate;
  task->url_ = delegate->GetTargetURL();
  msg_dispatcher->PostTask(task);
}

void Window::OnBrowserDestroyed(AcfRefPtr<AcfBrowser> browser) {
  std::cout << "OnBrowserDestroyed\n";

  browser_weak_ptr_ = nullptr;
  for (auto iter = g_browsers.begin(); iter != g_browsers.end(); iter++) {
    if ((*iter)->IsSame(browser)) {
      std::cout << "Remove browser\n";
      g_browsers.erase(iter);
      break;
    }
  }
}

void Window::OnLoadingStateChanged(AcfRefPtr<AcfBrowser> browser,
                                   bool show_loading_ui) {
  std::cout << "OnLoadingStateChanged\n";

  if (back_button_)
    EnableWindow(back_button_, browser->CanGoBack());
  if (forward_button_)
    EnableWindow(forward_button_, browser->CanGoForward());
  if (reload_button_)
    EnableWindow(reload_button_, !browser->IsLoading());
  if (stop_button_)
    EnableWindow(stop_button_, browser->IsLoading());
}

void Window::OnNavigationStateChanged(AcfRefPtr<AcfBrowser> browser,
                                      NavigationTypes flags) {
  std::cout << "OnNavigationStateChanged\n";
}

void Window::OnTitleChanged(AcfRefPtr<AcfBrowser> browser,
                            const AcfString& title) {
  AcfString rtitle = title.ToString() + " - acfclient";
  SetWindowText(window_, (LPWSTR)rtitle.ToString16().c_str());
}

void Window::OnAddressChanged(AcfRefPtr<AcfBrowser> browser,
                              const AcfString& address) {
  SetWindowText(edit_control_, (LPWSTR)address.ToString16().c_str());
}

void Window::OnFullscreenStateChanged(AcfRefPtr<AcfBrowser> browser,
                                      bool fullscreen) {
  std::cout << "OnFullscreenStateChanged: " << fullscreen << "\n";
}

}  // namespace acfclient