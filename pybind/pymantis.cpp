#include <pybind11/pybind11.h>
#include "mantis/mantis.h"
#include "classes/time_tag.hpp"
#include "errors/error_codes.hpp"
#include "errors/metadata_errors.hpp"
#include "msdr/msdr_params.hpp"
#include "mchannel/mchannel.hpp"
#include "device_manager/device_manager.hpp"
#include "classes/mtx_metadata.hpp"
#include "classes/mrx_metadata.hpp"
#include "utilities/prints.hpp"

namespace py = pybind11;


PYBIND11_MODULE(mantis, m) {
    m.attr("__version__") = MANTIS_VERSION;
// classes
    bind_time_tag(m);
    bind_errors(m);
    bind_msdr_params(m);
    bind_metadata_errors(m);
    bind_channels(m);
    bind_device_manager(m);
    bind_tx_metadata(m);
    bind_rx_metadata(m);

// namespaces
    py::module_ utils = m.def_submodule("utils", "mantis utility functions");
    bind_prints(utils);
}