max_value <- max(dataset$wealth_standard_deviation)
min_value <- min(dataset$wealth_standard_deviation)
mean_value <- mean(dataset$wealth_standard_deviation)
sd_value <- sd(dataset$wealth_standard_deviation)

breaks_values <- c(min_value, mean_value - sd_value, mean_value + sd_value, max_value)

donations_000 <- table(cut(dataset$wealth_standard_deviation[dataset$D == 0], breaks = breaks_values))
donations_050 <- table(cut(dataset$wealth_standard_deviation[dataset$D == 0.5], breaks = breaks_values))
donations_100 <- table(cut(dataset$wealth_standard_deviation[dataset$D == 1], breaks = breaks_values))

crosstable <- as.table(rbind(donations_000, donations_050, donations_100))

dimnames(crosstable) <- list("Probabilidade de Doações" = c("0%", "50%", "100%"), "Desvio Padrão de Riqueza" = c("Baixo", "Médio", "Alto"))

chisq.test(crosstable)
