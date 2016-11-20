.getLibs <- function() {
    linker_pattern <- "gcc|clang|g\\+\\+"

    shlib_ld <- system("R CMD config SHLIB_LD", intern=TRUE)
    shlib_cxxld <- system("R CMD config SHLIB_CXXLD", intern=TRUE)

    shlib_ld_results <- system(paste0(shlib_ld, " --version"), intern=TRUE)
    shlib_cxxld <- system(paste0(shlib_cxxld, " --version"), intern=TRUE)

    shlib_ld_good <- any(grepl(linker_pattern, shlib_ld_results))
    shlib_cxxld_good <- any(grepl(linker_pattern, shlib_cxxld_results))

    libs <- if (shlib_ld_good && shlib_cxxld_good) "-Wl,-S" else ""

    libs
}

inlineCxxPlugin <- Rcpp:::Rcpp.plugin.maker(libs = .getLibs())
