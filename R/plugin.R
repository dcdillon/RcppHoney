.getLibs <- function() {
    linker_pattern <- "gcc|clang|g\\+\\+"

    shlib_ld <- system(paste0(file.path(R.home("bin"), "R"),
        " CMD config SHLIB_LD"), intern=TRUE)
    shlib_cxxld <- system(paste0(file.path(R.home("bin"), "R"),
        " CMD config SHLIB_CXXLD"), intern=TRUE)

    shlib_ld_good <- FALSE
    shlib_cxxld_good <- FALSE
    
    if (shlib_ld != "") {
        shlib_ld_good <- tryCatch({
            shlib_ld_results <- system(paste0(shlib_ld, " --version"), intern=TRUE)
            shlib_ld_good <- any(grepl(linker_pattern, shlib_ld_results))
            shlib_ld_good
        }, warning = function(w) {
            return(FALSE)
        }, error = function(e) {
            return(FALSE)
        })
    } else {
        shlib_ld_good <- TRUE
    }
    
    if (shlib_cxxld != "") {
        shlib_cxxld_good <- tryCatch({
            shlib_cxxld_results <- system(paste0(shlib_ld, " --version"), intern=TRUE)
            shlib_cxxld_good <- any(grepl(linker_pattern, shlib_ld_results))
            shlib_cxxld_good
        }, warning = function(w) {
            return(FALSE)
        }, error = function(e) {
            return(FALSE)
        })
    } else {
        shlib_cxxld_good <- TRUE
    }

    libs <- if (shlib_ld_good && shlib_cxxld_good) "-Wl,-S" else ""

    libs
}

inlineCxxPlugin <- Rcpp:::Rcpp.plugin.maker(libs = .getLibs())
