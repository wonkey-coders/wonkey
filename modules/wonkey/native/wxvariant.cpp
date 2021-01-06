
#include "wxvariant.h"

wxVariant::RepBase wxVariant::_null;

template struct wxVariant::Rep<wxBool>;
template struct wxVariant::Rep<wxByte>;
template struct wxVariant::Rep<wxUByte>;
template struct wxVariant::Rep<wxShort>;
template struct wxVariant::Rep<wxUShort>;
template struct wxVariant::Rep<wxInt>;
template struct wxVariant::Rep<wxUInt>;
template struct wxVariant::Rep<wxLong>;
template struct wxVariant::Rep<wxULong>;
template struct wxVariant::Rep<wxFloat>;
template struct wxVariant::Rep<wxDouble>;
template struct wxVariant::Rep<wxString>;

