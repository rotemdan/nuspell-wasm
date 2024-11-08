/* Copyright 2016-2024 Dimitrij Mijoski
 *
 * This file is part of Nuspell.
 *
 * Nuspell is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Nuspell is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Nuspell.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file
 * @brief Finding dictionaries.
 */

#ifndef NUSPELL_FINDER_HXX
#define NUSPELL_FINDER_HXX

#include "defines.hxx"
#include "nuspell_export.h"

#include <filesystem>
#include <string>
#include <utility>
#include <vector>

#ifdef _MSC_VER
#define NUSPELL_MSVC_PRAGMA_WARNING(x) __pragma(warning(x))
#else
#define NUSPELL_MSVC_PRAGMA_WARNING(x)
#endif
NUSPELL_MSVC_PRAGMA_WARNING(push)
NUSPELL_MSVC_PRAGMA_WARNING(disable : 4251)

namespace nuspell {
NUSPELL_BEGIN_INLINE_NAMESPACE

NUSPELL_EXPORT auto
append_default_dir_paths(std::vector<std::filesystem::path>& paths) -> void;
NUSPELL_EXPORT auto
append_libreoffice_dir_paths(std::vector<std::filesystem::path>& paths) -> void;
NUSPELL_EXPORT auto
search_dirs_for_one_dict(const std::vector<std::filesystem::path>& dir_paths,
                         const std::filesystem::path& dict_name_stem)
    -> std::filesystem::path;
NUSPELL_EXPORT auto
search_dirs_for_dicts(const std::vector<std::filesystem::path>& dir_paths,
                      std::vector<std::filesystem::path>& dict_list) -> void;
NUSPELL_EXPORT auto search_default_dirs_for_dicts()
    -> std::vector<std::filesystem::path>;

NUSPELL_DEPRECATED_EXPORT
auto append_default_dir_paths(std::vector<std::string>& paths) -> void;

NUSPELL_DEPRECATED_EXPORT auto
append_libreoffice_dir_paths(std::vector<std::string>& paths) -> void;

NUSPELL_DEPRECATED_EXPORT auto search_dir_for_dicts(
    const std::string& dir_path,
    std::vector<std::pair<std::string, std::string>>& dict_list) -> void;

NUSPELL_DEPRECATED_EXPORT auto search_dirs_for_dicts(
    const std::vector<std::string>& dir_paths,
    std::vector<std::pair<std::string, std::string>>& dict_list) -> void;

NUSPELL_DEPRECATED_EXPORT auto search_default_dirs_for_dicts(
    std::vector<std::pair<std::string, std::string>>& dict_list) -> void;

NUSPELL_DEPRECATED_EXPORT auto find_dictionary(
    const std::vector<std::pair<std::string, std::string>>& dict_list,
    const std::string& dict_name)
    -> std::vector<std::pair<std::string, std::string>>::const_iterator;

/**
 * @internal
 * @brief Don't use this except from Nuspell CLI tool.
 *
 * There are no promises of the API.
 */
class NUSPELL_DEPRECATED_EXPORT Dict_Finder_For_CLI_Tool {
	std::vector<std::string> dir_paths;
	std::vector<std::pair<std::string, std::string>> dict_multimap;

      public:
	Dict_Finder_For_CLI_Tool();
	auto& get_dir_paths() const { return dir_paths; }
	auto& get_dictionaries() const { return dict_multimap; }
	auto get_dictionary_path(const std::string& dict) const -> std::string;
};

/**
 * @internal
 * @brief Don't use this except from Nuspell CLI tool.
 *
 * There are no promises of the API.
 */
class NUSPELL_EXPORT Dict_Finder_For_CLI_Tool_2 {
	std::vector<std::filesystem::path> dir_paths;

      public:
	Dict_Finder_For_CLI_Tool_2();
	auto& get_dir_paths() const { return dir_paths; }
	auto get_dictionary_path(const std::filesystem::path& dict) const
	    -> std::filesystem::path;
};

NUSPELL_END_INLINE_NAMESPACE
} // namespace nuspell
NUSPELL_MSVC_PRAGMA_WARNING(pop)
#endif // NUSPELL_FINDER_HXX
