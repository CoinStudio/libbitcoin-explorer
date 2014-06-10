/**
 * Copyright (c) 2011-2014 sx developers (see AUTHORS)
 *
 * This file is part of sx.
 *
 * sx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
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
#ifndef SX_COMMAND_HPP
#define SX_COMMAND_HPP

#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <sx/utility/config.hpp>
#include <sx/utility/console.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

namespace sx {

#define SX_VARIABLE_CONFIG "config"

/**
 * Abstract base class for definition of each SX command.
 */
class command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol() { return "not-implemented"; }

    /**
     * The symbolic (not localizable) command name, lower case.
     *
     * @return  Example: "fetch-transaction"
     */
    virtual const char* name()
    {
        return symbol();
    }

    /**
     * The localizable command category name, upper case.
     *
     * @return  Example: "ONLINE (OBELISK)"
     */
    virtual const char* category()
    {
        return symbol();
    }

    /**
     * The localizable command subcategory name, upper case.
     *
     * @return  Example: "BLOCKCHAIN QUERIES"
     */
    virtual const char* subcategory()
    {
        return symbol();
    }

    /**
     * The localizable command description, multiple lines, punctuated.
     *
     * @return  Example:
     * "Fetch a raw transaction using a network connection to"
     * "make requests against the obelisk load balancer back end."
     */
    virtual const std::vector<const char*> description()
    {
        return { symbol() };
    }

    /**
     * The non-localizable command usage examples, multiple lines.
     *
     * @return  Example:
     * "sx fetch-transaction HASH"
     */
    virtual const std::vector<const char*> example()
    {
        return { symbol() };
    }

    /**
     * The localizable command explanation, multiple lines, punctuated.
     *
     * @return  Example:
     * "$ sx fetch-transaction ... # fetches raw data"
     */
    virtual const std::vector<const char*> explanation()
    {
        return { symbol() };
    }
    
    /**
     * Invoke the command.
     *
     * @return  The appropriate console return code { -1, 0, 1 }.
     */
    virtual console_result invoke()
    {
        return console_result::failure;
    }

    /**
     * Load command argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     *
     * @param[out] definitions  The defined program argument definitions.
     */
    virtual void load_arguments(
        boost::program_options::positional_options_description& definitions)
    {
    }

    /**
     * Load environment variable definitions.
     *
     * @param[out] definitions  The defined program argument definitions.
     */
    virtual void load_environment(
        boost::program_options::options_description& definitions)
    {
        using namespace boost::program_options;
        definitions.add_options()
            /* This composes with the command line options. */
            (
                SX_VARIABLE_CONFIG, 
                value<boost::filesystem::path>()
                    ->composing()->default_value(config_default()),
                "The path and file name for the configuration settings file for this application."
            );
    }

    /**
     * Load command option definitions.
     * The implicit_value call allows flags to be strongly-typed on read while
     * allowing but not requiring a value on the command line for the option.
     *
     * BUGBUG: see boost bug/fix: svn.boost.org/trac/boost/ticket/8009
     *
     * @param[out] definitions  The defined program option definitions.
     */
    virtual void load_options(
        boost::program_options::options_description& definitions)
    {
    }
    
    /**
     * Load configuration setting definitions.
     *
     * @param[out] definitions  The defined program argument definitions.
     */
    virtual void load_settings(
        boost::program_options::options_description& definitions)
    {
        using namespace boost::program_options;
        definitions.add_options()
            (
                "general.testnet",
                value<bool>(&settings.general.testnet),
                "Set to true in order to operate this application using Bitcoin testnet (vs. mainnet) addressing and blockchain data. This option is EXPERIMENTAL because other  libraries on which this application depends must currently be compiled with the testnet flag to ensure complete testnet semantics."
            )
            (
                "obelisk.client-certificate",
                value<boost::filesystem::path>(&settings.obelisk.client_certificate),
                "The path to a private key certificate (file) that the server can use to prove the identity of this client. This is useful in authorizing remote administration of the server. The associated public key would need to be known by the server. Use the CZMQ program 'makecert' to generate the key certificate. For example: /home/genjix/.sx.cert"
            )
            (
                "obelisk.server-public-key",
                value<std::string>(&settings.obelisk.server_public_key),
                "The public key of the server to which this application may connect. This must be the key for server specified by the 'service' option. For example: W=GRFxHUuUN#En3MI]f{}X:KWnV=pRZ$((byg=:h"
            )
            (
                "obelisk.service",
                value<std::string>(&settings.obelisk.service)->default_value("tcp://obelisk.unsystem.net:8081"),
                "The URI of the server to which this application may connect."
            );
    }      

protected:

    /**
     * This base class is abstract but not pure virtual, so prevent direct 
     * construction here.
     */
    command() {}

    /**
     * Configuration settings file bound variables.
     */
    struct
    {
        struct
        {
            bool testnet;
        } general;
        struct
        {
            boost::filesystem::path client_certificate;
            std::string server_public_key;
            std::string service;
        } obelisk;
    } settings;
    
    /**
     * Environment variable bound variables.
     */
    struct
    {
        boost::filesystem::path config;
    } environment;
};

} // sx

#endif
