#ifndef ACF_TYPES_H_
#define ACF_TYPES_H_

#include "include/internal/acf_string.h"
#include "include/internal/acf_enums.h"
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

#ifdef __cplusplus
}
#endif

#endif