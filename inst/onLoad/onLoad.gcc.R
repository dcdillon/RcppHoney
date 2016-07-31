.onLoad <- function(libname, pkgname) {
    plug <- Rcpp:::Rcpp.plugin.maker(
        libs = "-Wl,-S")

    registerPlugin("RcppHoney", plug)
}
