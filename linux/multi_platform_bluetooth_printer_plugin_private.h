#include <flutter_linux/flutter_linux.h>

#include "include/multi_platform_bluetooth_printer/multi_platform_bluetooth_printer_plugin.h"

// This file exposes some plugin internals for unit testing. See
// https://github.com/flutter/flutter/issues/88724 for current limitations
// in the unit-testable API.

// Handles the getPlatformVersion method call.
FlMethodResponse *get_platform_version();
