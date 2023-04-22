#ifndef ACF_ENUMS_H_
#define ACF_ENUMS_H_

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

///
/// Supported value types.
///
typedef enum {
  VTYPE_INVALID = 0,
  VTYPE_NULL,
  VTYPE_BOOL,
  VTYPE_INT,
  VTYPE_DOUBLE,
  VTYPE_STRING,
  VTYPE_BINARY,
  VTYPE_DICTIONARY,
  VTYPE_LIST,
} acf_value_type_t;

///
/// Cookie priority values.
///
typedef enum {
  ACF_COOKIE_PRIORITY_LOW = 0,
  ACF_COOKIE_PRIORITY_MEDIUM = 1,
  ACF_COOKIE_PRIORITY_HIGH = 2,
} acf_cookie_priority_t;

///
/// Cookie same site values.
///
typedef enum {
  ACF_COOKIE_SAME_SITE_UNSPECIFIED = -1,
  ACF_COOKIE_SAME_SITE_NO_RESTRICTION = 0,
  ACF_COOKIE_SAME_SITE_LAX_MODE = 1,
  ACF_COOKIE_SAME_SITE_STRICT_MODE = 2,
} acf_cookie_same_site_t;

///
/// Supported context menu type flags.
///
typedef enum {
  ///
  /// No node is selected.
  ///
  CM_TYPEFLAG_NONE = 0,
  ///
  /// The top page is selected.
  ///
  CM_TYPEFLAG_PAGE = 1 << 0,
  ///
  /// A subframe page is selected.
  ///
  CM_TYPEFLAG_FRAME = 1 << 1,
  ///
  /// A link is selected.
  ///
  CM_TYPEFLAG_LINK = 1 << 2,
  ///
  /// A media node is selected.
  ///
  CM_TYPEFLAG_MEDIA = 1 << 3,
  ///
  /// There is a textual or mixed selection that is selected.
  ///
  CM_TYPEFLAG_SELECTION = 1 << 4,
  ///
  /// An editable element is selected.
  ///
  CM_TYPEFLAG_EDITABLE = 1 << 5,
} acf_context_menu_type_flags_t;

///
/// Supported menu item types.
///
typedef enum {
  MENUITEMTYPE_NONE = 0,
  MENUITEMTYPE_COMMAND,
  MENUITEMTYPE_CHECK,
  MENUITEMTYPE_RADIO,
  MENUITEMTYPE_SEPARATOR,
  MENUITEMTYPE_SUBMENU,
} acf_menu_item_type_t;

///
/// Supported context menu media types. These constants match their equivalents
/// in Chromium's ContextMenuDataMediaType and should not be renumbered.
///
typedef enum {
  ///
  /// No special node is in context.
  ///
  CM_MEDIATYPE_NONE = 0,
  ///
  /// An image node is selected.
  ///
  CM_MEDIATYPE_IMAGE,
  ///
  /// A video node is selected.
  ///
  CM_MEDIATYPE_VIDEO,
  ///
  /// An audio node is selected.
  ///
  CM_MEDIATYPE_AUDIO,
  ///
  /// An canvas node is selected.
  ///
  CM_MEDIATYPE_CANVAS,
  ///
  /// A file node is selected.
  ///
  CM_MEDIATYPE_FILE,
  ///
  /// A plugin node is selected.
  ///
  CM_MEDIATYPE_PLUGIN,
} acf_context_menu_media_type_t;

///
/// Supported context menu media state bit flags. These constants match their
/// equivalents in Chromium's ContextMenuData::MediaFlags and should not be
/// renumbered.
///
typedef enum {
  CM_MEDIAFLAG_NONE = 0,
  CM_MEDIAFLAG_IN_ERROR = 1 << 0,
  CM_MEDIAFLAG_PAUSED = 1 << 1,
  CM_MEDIAFLAG_MUTED = 1 << 2,
  CM_MEDIAFLAG_LOOP = 1 << 3,
  CM_MEDIAFLAG_CAN_SAVE = 1 << 4,
  CM_MEDIAFLAG_HAS_AUDIO = 1 << 5,
  CM_MEDIAFLAG_CAN_TOGGLE_CONTROLS = 1 << 6,
  CM_MEDIAFLAG_CONTROLS = 1 << 7,
  CM_MEDIAFLAG_CAN_PRINT = 1 << 8,
  CM_MEDIAFLAG_CAN_ROTATE = 1 << 9,
  CM_MEDIAFLAG_CAN_PICTURE_IN_PICTURE = 1 << 10,
  CM_MEDIAFLAG_PICTURE_IN_PICTURE = 1 << 11,
  CM_MEDIAFLAG_CAN_LOOP = 1 << 12,
} acf_context_menu_media_state_flags_t;

///
/// Supported context menu edit state bit flags. These constants match their
/// equivalents in Chromium's ContextMenuDataEditFlags and should not be
/// renumbered.
///
typedef enum {
  CM_EDITFLAG_NONE = 0,
  CM_EDITFLAG_CAN_UNDO = 1 << 0,
  CM_EDITFLAG_CAN_REDO = 1 << 1,
  CM_EDITFLAG_CAN_CUT = 1 << 2,
  CM_EDITFLAG_CAN_COPY = 1 << 3,
  CM_EDITFLAG_CAN_PASTE = 1 << 4,
  CM_EDITFLAG_CAN_DELETE = 1 << 5,
  CM_EDITFLAG_CAN_SELECT_ALL = 1 << 6,
  CM_EDITFLAG_CAN_TRANSLATE = 1 << 7,
  CM_EDITFLAG_CAN_EDIT_RICHLY = 1 << 8,
} acf_context_menu_edit_state_flags_t;

#endif