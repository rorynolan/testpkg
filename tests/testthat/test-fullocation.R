test_that("list fullocation works", {
  int_mat <- rbind(c(5L, 6L), c(7L, 10L), c(20L, 30L))
  expect_equal(
    fullocate(int_mat),
    list(c(5L, 6L), c(7L, 10L), c(11L, 19L), c(20L, 30L))
  )
})
