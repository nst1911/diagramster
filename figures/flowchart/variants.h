#ifndef VARIANTS_H
#define VARIANTS_H

#include <QString>

namespace diagramster {
namespace flowchart {
namespace variants {

#define FLOWCHART_VARIANT_PREFIX "flowchart-"

constexpr const char* TERMINAL            = FLOWCHART_VARIANT_PREFIX"terminal";
constexpr const char* PROCESS             = FLOWCHART_VARIANT_PREFIX"process";
constexpr const char* DECISION            = FLOWCHART_VARIANT_PREFIX"decision";
constexpr const char* INPUT_OUTPUT        = FLOWCHART_VARIANT_PREFIX"input-output";
constexpr const char* PREDEFINED_PROCESS  = FLOWCHART_VARIANT_PREFIX"predefined-process";
constexpr const char* ON_PAGE_CONNECTOR   = FLOWCHART_VARIANT_PREFIX"on-page-connector";
constexpr const char* OFF_PAGE_CONNECTOR  = FLOWCHART_VARIANT_PREFIX"off-page-connector";
constexpr const char* FLOWLINE            = FLOWCHART_VARIANT_PREFIX"flowline";

#undef FLOWCHART_VARIANT_PREFIX

}
}
}

#endif // VARIANTS_H
