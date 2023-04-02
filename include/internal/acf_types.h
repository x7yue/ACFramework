#ifndef ACF_TYPES_H_
#define ACF_TYPES_H_

#include "include/internal/acf_string.h"
#include <wtypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Environment create params
///
typedef struct _acf_environment_settings_t {
  ///
  /// Size of this structure.
  ///
  size_t size;

  /// Pass the command line to the new process
  acf_string_t command_line;

  /// The chromium's cache & userdata dir
  acf_string_t user_data_dir;
} acf_environment_settings_t;

/// Browser create params
///
typedef struct _acf_browser_create_params_t {
  ///
  /// Size of this structure.
  ///
  size_t size;

  /// Parent window, if nullptr the browser will show with popup.
  HWND parent;

  /// initial window visible
  bool visible;

  /// pos & size in parent
  int x;
  int y;
  int width;
  int height;
} acf_browser_create_params_t;

typedef enum {
  /// New contents, included javascript 'window.open'
  /// or click on normal link
  NEW_CONTENTS = 0,

  /// Includes open url in menu context,
  /// and other chrome built-in operation.
  OPEN_FROM_TAB_URL,
} acf_new_window_source_t;

typedef enum {
  UNKNOWN,
  CURRENT_TAB,
  /// Indicates that only one tab with the url should exist in the same window.
  SINGLETON_TAB,
  NEW_FOREGROUND_TAB,
  NEW_BACKGROUND_TAB,
  NEW_POPUP,
  NEW_WINDOW,
  SAVE_TO_DISK,
  OFF_THE_RECORD,
  IGNORE_ACTION,
  /// Activates an existing tab containing the url, rather than navigating.
  /// This is similar to SINGLETON_TAB, but searches across all windows from
  /// the current profile and anonymity (instead of just the current one);
  /// closes the current tab on switching if the current tab was the NTP with
  /// no session history; and behaves like CURRENT_TAB instead of
  /// NEW_FOREGROUND_TAB when no existing tab is found.
  SWITCH_TO_TAB,
  /// Creates a new document picture-in-picture window showing a child WebView.
  NEW_PICTURE_IN_PICTURE,
  /// Update when adding a new disposition.
  MAX_VALUE = NEW_PICTURE_IN_PICTURE,
} acf_new_window_disposition_t;

typedef enum {
  INVALIDATE_TYPE_URL = 1 << 0,    /// The URL has changed.
  INVALIDATE_TYPE_TAB = 1 << 1,    /// The favicon, app icon, or crashed
                                   /// state changed.
  INVALIDATE_TYPE_LOAD = 1 << 2,   /// The loading state has changed.
  INVALIDATE_TYPE_TITLE = 1 << 3,  /// The title changed.
  INVALIDATE_TYPE_AUDIO = 1 << 4,  /// The tab became audible or
                                   /// inaudible.
                                   /// TODO(crbug.com/846374):
                                   /// remove this.

  INVALIDATE_TYPE_ALL = (1 << 5) - 1,
} acf_navigation_types_t;

typedef enum {
  DATA_TYPE_HISTORY = 1 << 0,
  DATA_TYPE_FORM_DATA = 1 << 1,
  DATA_TYPE_PASSWORDS = 1 << 2,
  DATA_TYPE_SITE_USAGE_DATA = 1 << 3,
  DATA_TYPE_DURABLE_PERMISSION = 1 << 4,
  DATA_TYPE_EXTERNAL_PROTOCOL_DATA = 1 << 5,
  DATA_TYPE_HOSTED_APP_DATA_TEST_ONLY = 1 << 6,
  DATA_TYPE_CONTENT_SETTINGS = 1 << 7,
  DATA_TYPE_BOOKMARKS = 1 << 8,
  DATA_TYPE_ISOLATED_ORIGINS = 1 << 9,
  DATA_TYPE_ACCOUNT_PASSWORDS = 1 << 10,
  DATA_TYPE_LOCAL_CUSTOM_DICTIONARY = 1 << 11,
  DATA_TYPE_SITE_DATA = 1 << 12,
  IMPORTANT_SITES_DATA_TYPES = 1 << 13,
  FILTERABLE_DATA_TYPES = 1 << 14,
  DEFERRED_COOKIE_DELETION_DATA_TYPES = 1 << 15,

  ALL_DATA_TYPES = 0xffffffff,
} acf_remove_data_type_t;

#ifdef __cplusplus
}
#endif

#endif