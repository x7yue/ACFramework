#include "include/acf_context_menu.h"
#include "include/acf_browser.h"

#include "wrapper_utility.h"

extern DWORD acf_cpp_fntable_authcallback[];
extern DWORD acf_cpp_fntable_menucallback[];
extern DWORD acf_cpp_fntable_menuparams[];
extern DWORD acf_cpp_fntable_menumodel[];

namespace {

void ACF_CALLBACK auth_continue(AcfLoginDelegate* obj, LPCSTR username,
                               LPCSTR password) {
  obj->Continue(username, password);
}

void ACF_CALLBACK auth_cancel(AcfLoginDelegate* obj) { obj->Cancel(); }

void ACF_CALLBACK menu_callback(AcfContextMenuCallback* callback,
                               bool suppress) {
  callback->Continue(suppress);
}

} // namespace

DWORD acf_cpp_fntable_authcallback[] = {
    (DWORD)auth_continue,
    (DWORD)auth_cancel,
};

DWORD acf_cpp_fntable_menucallback[] = {
    (DWORD)menu_callback,
};

namespace {

int ACF_CALLBACK menu_params_get_x(AcfContextMenuParams* obj) {
  return obj->GetXCoord();
}

int ACF_CALLBACK menu_params_get_y(AcfContextMenuParams* obj) {
  return obj->GetYCoord();
}

acf_context_menu_type_flags_t ACF_CALLBACK
menu_params_get_type(AcfContextMenuParams* obj) {
  return obj->GetTypeFlags();
}

LPCSTR ACF_CALLBACK menu_params_get_link_url(AcfContextMenuParams* obj) {
  return GetEString(obj->GetLinkUrl());
}

LPCSTR ACF_CALLBACK menu_params_get_unfiltered_link_url(AcfContextMenuParams* obj) {
  return GetEString(obj->GetUnfilteredLinkUrl());
}

LPCSTR ACF_CALLBACK menu_params_get_source_url(AcfContextMenuParams* obj) {
  return GetEString(obj->GetSourceUrl());
}

LPCSTR ACF_CALLBACK menu_params_get_page_url(AcfContextMenuParams* obj) {
  return GetEString(obj->GetPageUrl());
}

LPCSTR ACF_CALLBACK menu_params_get_frame_url(AcfContextMenuParams* obj) {
  return GetEString(obj->GetFrameUrl());
}

LPCSTR ACF_CALLBACK menu_params_get_frame_charset(AcfContextMenuParams* obj) {
  return GetEString(obj->GetFrameCharset());
}

acf_context_menu_media_type_t ACF_CALLBACK menu_params_get_media_type(AcfContextMenuParams* obj) {
  return obj->GetMediaType();
}

acf_context_menu_media_state_flags_t ACF_CALLBACK
menu_params_get_media_state(AcfContextMenuParams* obj) {
  return obj->GetMediaStateFlags();
}

LPCSTR ACF_CALLBACK menu_params_get_selection_text(AcfContextMenuParams* obj) {
  return GetEString(obj->GetSelectionText());
}

bool ACF_CALLBACK menu_params_is_editable(AcfContextMenuParams* obj) {
  return obj->IsEditable();
}

acf_context_menu_edit_state_flags_t ACF_CALLBACK menu_params_get_edit_state(AcfContextMenuParams* obj) {
  return obj->GetEditStateFlags();
}

} // namespace

DWORD acf_cpp_fntable_menuparams[] = {
    (DWORD)menu_params_get_x,
    (DWORD)menu_params_get_y,
    (DWORD)menu_params_get_type, (DWORD)menu_params_get_link_url,
    (DWORD)menu_params_get_unfiltered_link_url,
    (DWORD)menu_params_get_source_url,
    (DWORD)menu_params_get_page_url,
    (DWORD)menu_params_get_frame_url,
    (DWORD)menu_params_get_frame_charset,
    (DWORD)menu_params_get_media_type,
    (DWORD)menu_params_get_media_state,
    (DWORD)menu_params_get_selection_text,
    (DWORD)menu_params_is_editable,
    (DWORD)menu_params_get_edit_state,
};

namespace {

bool menu_model_is_submenu(AcfContextMenuModel* obj) {
  return obj->IsSubMenu();
}

bool menu_model_clear(AcfContextMenuModel* obj) {
  return obj->Clear();
}

int menu_model_get_count(AcfContextMenuModel* obj) {
  return obj->GetCount();
}

bool menu_model_insert_separator(AcfContextMenuModel* obj, int index) {
  return obj->InsertSeparatorAt(index);
}

bool menu_model_insert_item(AcfContextMenuModel* obj, int index, int command_id,
                            LPCSTR name) {
  return obj->InsertItemAt(index, command_id, name);
}

bool menu_model_insert_check_item(AcfContextMenuModel* obj, int index, int command_id,
                            LPCSTR name) {
  return obj->InsertCheckItemAt(index, command_id, name);
}

bool menu_model_insert_radio_item(AcfContextMenuModel* obj, int index,
                                  int command_id, LPCSTR name, int group) {
  return obj->InsertRadioItemAt(index, command_id, name, group);
}

bool menu_model_insert_submenu_item(AcfContextMenuModel* obj, int index,
                                  int command_id, LPCSTR name, DWORD* retObj) {
  AcfRefPtr<AcfContextMenuModel> submenu = obj->InsertSubMenuAt(index, command_id, name);

  if (retObj) {
    submenu->AddRef();
    retObj[1] = (DWORD)submenu.get();
    retObj[2] = (DWORD)acf_cpp_fntable_menumodel;
  }

  return !!submenu.get();
}

bool menu_model_remove(AcfContextMenuModel* obj, int index) {
  return obj->RemoveAt(index);
}

int menu_model_get_command_id(AcfContextMenuModel* obj, int index) {
  return obj->GetCommandIdAt(index);
}

int menu_model_get_index_of(AcfContextMenuModel* obj, int index) {
  return obj->GetIndexOf(index);
}

bool menu_model_set_command_id(AcfContextMenuModel* obj, int index, int command_id) {
  return obj->SetCommandIdAt(index, command_id);
}

bool menu_model_set_check(AcfContextMenuModel* obj, int index, bool v) {
  return obj->SetCheckedAt(index, v);
}

bool menu_model_get_check(AcfContextMenuModel* obj, int index) {
  return obj->IsCheckedAt(index);
}

bool menu_model_set_enabled(AcfContextMenuModel* obj, int index, bool v) {
  return obj->SetEnabledAt(index, v);
}

bool menu_model_get_enabled(AcfContextMenuModel* obj, int index) {
  return obj->IsEnabledAt(index);
}

bool menu_model_set_visibled(AcfContextMenuModel* obj, int index, bool v) {
  return obj->SetVisibleAt(index, v);
}

bool menu_model_get_visibled(AcfContextMenuModel* obj, int index) {
  return obj->IsVisibleAt(index);
}

bool menu_model_set_label(AcfContextMenuModel* obj, int index, LPCSTR v) {
  return obj->SetLabelAt(index, v);
}

LPCSTR menu_model_get_label(AcfContextMenuModel* obj, int index) {
  return GetEString(obj->GetLabelAt(index));
}

bool menu_model_set_group_id(AcfContextMenuModel* obj, int index, int v) {
  return obj->SetGroupIdAt(index, v);
}

int menu_model_get_group_id(AcfContextMenuModel* obj, int index) {
  return obj->GetGroupIdAt(index);
}

acf_menu_item_type_t menu_model_get_item_type(AcfContextMenuModel* obj, int index) {
  return obj->GetTypeAt(index);
}

} // namespace

DWORD acf_cpp_fntable_menumodel[] = {
    (DWORD)menu_model_is_submenu,
    (DWORD)menu_model_clear,
    (DWORD)menu_model_get_count,
    (DWORD)menu_model_insert_separator,
    (DWORD)menu_model_insert_item,
    (DWORD)menu_model_insert_check_item,
    (DWORD)menu_model_insert_radio_item,
    (DWORD)menu_model_insert_submenu_item,
    (DWORD)menu_model_remove,
    (DWORD)menu_model_get_command_id,
    (DWORD)menu_model_get_index_of,
    (DWORD)menu_model_set_command_id,
    (DWORD)menu_model_get_check,
    (DWORD)menu_model_set_check,
    (DWORD)menu_model_get_enabled,
    (DWORD)menu_model_set_enabled,
    (DWORD)menu_model_get_visibled,
    (DWORD)menu_model_set_visibled,
    (DWORD)menu_model_get_label,
    (DWORD)menu_model_set_label,
    (DWORD)menu_model_get_group_id,
    (DWORD)menu_model_set_group_id,
    (DWORD)menu_model_get_item_type,
};
