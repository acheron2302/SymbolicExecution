/* Copyright 2017 - 2023 R. Thomas
 * Copyright 2017 - 2023 Quarkslab
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef LIEF_MACHO_SYMBOL_CPP_C_API_
#define LIEF_MACHO_SYMBOL_CPP_C_API_

#include "LIEF/MachO/Binary.h"
#include "LIEF/MachO/Binary.hpp"

#include "LIEF/MachO/Symbol.h"
#include "LIEF/MachO/Symbol.hpp"

namespace LIEF {
namespace MachO {

void init_c_symbols(Macho_Binary_t* c_binary, Binary* binary);
void destroy_symbols(Macho_Binary_t* c_binary);

}
}

#endif