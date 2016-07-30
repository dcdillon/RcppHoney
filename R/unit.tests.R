# Copyright (C) 2010 - 2015  Dirk Eddelbuettel, Romain Francois and Douglas Bates
#
# This file is part of RcppHoney.
#
# RcppHoney is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# RcppHoney is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with RcppHoney.  If not, see <http://www.gnu.org/licenses/>.

unit_test_setup <- function(file = NULL, packages = NULL) {
    function(){
        if (!is.null(packages)) {
            for (p in packages) {
                suppressMessages(requireNamespace(p))
            }
        }
        if (!is.null(file)) {
            if (exists("pathRcppHoneyTests")) {
                sourceCpp(file.path(get("pathRcppHoneyTests"), "cpp", file))
            } else if (file.exists(file.path("cpp", file))) {
                sourceCpp(file.path( "cpp", file))
            } else {
                sourceCpp(system.file("unitTests", "cpp", file, package="RcppHoney"))
            }
        }
    }
}
