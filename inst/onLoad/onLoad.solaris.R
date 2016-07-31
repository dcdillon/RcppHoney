.onLoad <- function(libname, pkgname) {
    plug <- Rcpp:::Rcpp.plugin.maker(
        libs = "")

    registerPlugin("RcppHoney", plug)
}
