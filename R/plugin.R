# Copyright (C) 2016 Daniel C. Dillon
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

# Return the appropriate option to pass the linker to cause it to strip
# debugging symbols out of a shared library.  This only takes actual linkers
# (ld, gold, etc.) and not "wrappers" (gcc, clang, etc.).  Returns the option
# that the linker needs or empty string if it is unknown.
.getLinkerOptions <- function(cmd) {
  if (cmd != "") {
    output <- system(paste0(cmd, " --version"), intern=TRUE)
    
    if (grepl("^GNU ld", output[1])) {
      return("-S")
    } else if (grepl("^GNU gold", output[1])) {
      return("-S")
    }
  }
  
  return("")
}

# Given a linker (ld, gold, etc.) or a linker "wrapper" (gcc, clang, etc.),
# determine the option that can be passed to cause it to strip debugging
# symbols out of a shared library.  Returns the option needed by this
# executable to strip the library or empty string if it is unknown.
.getLinkerOrWrapperOptions <- function(cmd) {
  if (cmd != "") {
    # First see if this is a linker in its own right and what option it
    # will need.
    linkerOption <- .getLinkerOptions(cmd)
    
    if (linkerOption != "")
    {
      return(linkerOption)
    }
    
    # If it's not a linker, assume it's a "wrapper" and try to figure out
    # what linker it will actually call.
    output <- system(paste0(cmd, " --version"), intern=TRUE)
    
    if (grepl("gcc|clang|g\\+\\+", output[1])) {
      linkerCommand <- system(paste0(cmd, " --print-prog-name=ld"),
                              intern=TRUE)
      
      linkerOption <- .getLinkerOptions(linkerCommand)
      
      if (linkerOption != "") {
        return(paste0("-Wl,", linkerOption))
      }
    }
  }
  
  return("")
}

# Given the name of an R configuration value that specifies what command will
# be executed to link a shared library, return the command line options that
# can be passed to it to cause it to strip debugging symbols from the resulting
# shared library.  Returns empty string if it is unknown.
.getStripLinkerOption <- function(rConfigParam) {
    rLinkerCommand <- system(paste0(file.path(R.home("bin"), "R"),
                                    " CMD config ", rConfigParam), intern=TRUE)
    
    if (rLinkerCommand != "") {
      return(.getLinkerOrWrapperOptions(rLinkerCommand))
    }
    
    return("")
}

# If there is a single command line option that can be passed to all the linker
# executables that R will call, return it.  Return empty string otherwise.
.getUniversalStripLinkerOption <- function() {
  tryCatch({
    possibleLinkerOptions <- c()
    possibleLinkerOptions <- c(possibleLinkerOptions,
                               .getStripLinkerOption("SHLIB_LD"))
    possibleLinkerOptions <- c(possibleLinkerOptions,
                               .getStripLinkerOption("SHLIB_CXXLD"))
    
    # If all of the possible linkers will accept the same command, return it.
    if (all.equal(rep(possibleLinkerOptions[1], length(possibleLinkerOptions)),
                  possibleLinkerOptions)) {
      
      return(possibleLinkerOptions[1])
    }
  },
  warning = function(w) {return("")},
  error = function(e) {return("")})
  
  return("")
}

inlineCxxPlugin <- Rcpp:::Rcpp.plugin.maker(
    libs = .getUniversalStripLinkerOption())
