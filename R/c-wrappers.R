#' @useDynLib testpkg C_fullocate
fullocate <- function(int_mat) {
  .Call(C_fullocate, int_mat)
}
