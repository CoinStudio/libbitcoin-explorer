/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin-explorer.
 *
 * libbitcoin-explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <bitcoin/explorer/commands/ec-to-ek.hpp>

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/primitives/ek_private.hpp>

using namespace bc;
using namespace bc::bip38;
using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::explorer::primitives;

console_result ec_to_ek::invoke(std::ostream& output, std::ostream& error)
{
#ifdef WITH_ICU
    const auto uncompressed = get_uncompressed_option();
    const auto version = get_version_option();
    const auto& passphrase = get_passphrase_argument();
    const auto& secret = get_ec_private_key_argument();

    ek_private key;
    encrypt(key.data(), secret, passphrase, version, !uncompressed);

    output << key << std::endl;
    return console_result::okay;
#else
    error << BX_EC_TO_EK_REQUIRES_ICU << std::endl;
    return console_result::failure;
#endif
}
