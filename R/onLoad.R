.onLoad <- function(libname, pkgname) {

    sysname <- Sys.info()[['sysname']]

    if (sysname != "SunOS") {
    	plug <- Rcpp:::Rcpp.plugin.maker(
            libs = "-Wl,-S")
    } else {
        plug <- Rcpp:::Rcpp.plugin.maker(
            libs = "")
    }

    registerPlugin("RcppHoney", plug)
}
