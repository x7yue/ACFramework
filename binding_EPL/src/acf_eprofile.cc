#include "acf_eprofile.h"
#include "acf_Util.h"

extern DWORD acf_cpp_fntable_profile[];

namespace {

bool ACF_CALLBACK is_valid(AcfProfile* obj) { return obj->IsValid(); }

LPSTR ACF_CALLBACK get_path(AcfProfile* obj) {
  return GetEString(obj->GetPath());
}

void ACF_CALLBACK remove_browsing_data(AcfProfile* obj, int type, bool check,
                            void* token) {
  obj->RemoveBrowsingData((AcfProfile::RemoveDataType)type, check, token);
}

} // namespace

DWORD acf_cpp_fntable_profile[] = {
    (DWORD)is_valid,
    (DWORD)get_path,
    (DWORD)remove_browsing_data,
};
