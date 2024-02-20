from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score
import pandas as pd
import Dataset

def covid_binary(value):
    if value == "negative":
        return 0
    else:
        return 1

def home_treatment(v1, v2, v3):
    if v1 + v2 + v3 == 0:
        return 1
    else:
        return 0

def Covid():

    print("\n--------------------------------\n\n>> PACIENTES COM COVID:\n")
    print(Dataset.matrix["SARS-Cov-2 exam result"].value_counts())
    print()

    clf = RandomForestClassifier(n_estimators = 100)

    variables = ["Patient age quantile", "Patient addmited to regular ward (1=yes, 0=no)", "Patient addmited to semi-intensive unit (1=yes, 0=no)", "Patient addmited to intensive care unit (1=yes, 0=no)", "Hematocrit", "Hemoglobin", "Platelets", "Mean platelet volume ", "Lymphocytes", "Mean corpuscular hemoglobin concentration (MCHC)", "Leukocytes", "Basophils", "Mean corpuscular hemoglobin (MCH)", "Eosinophils", "Mean corpuscular volume (MCV)", "Monocytes", "Red blood cell distribution width (RDW)", "Serum Glucose", "Neutrophils", "Urea", "Proteina C reativa mg/dL", "Creatinine", "Potassium", "Sodium", "Alanine transaminase", "Aspartate transaminase", "Ionized calcium "]
    x = Dataset.matrix[variables]
    x = x.fillna(0)
    y = Dataset.matrix["SARS-Cov-2 exam result"]

    clf.fit(x, y)
    results = clf.predict(x)
    print(f"Precisão de {accuracy_score(y, results)}\n")

    columns_relevance = pd.DataFrame({"Variavel": list(x.columns), "Importancia": clf.feature_importances_})
    columns_relevance.sort_values("Importancia", ascending = False)
    print(columns_relevance.head(10))

def RegularWard():

    print("\n--------------------------------\n\n>> PACIENTES EM ENFERMARIA REGULAR:\n")
    print(Dataset.matrix["Patient addmited to regular ward (1=yes, 0=no)"].value_counts())
    print()

    clf = RandomForestClassifier(n_estimators = 100)

    Dataset.matrix["CovidBinario"] = Dataset.matrix["SARS-Cov-2 exam result"].map(covid_binary)

    variables = ["Patient age quantile", "CovidBinario", "Patient addmited to semi-intensive unit (1=yes, 0=no)", "Patient addmited to intensive care unit (1=yes, 0=no)", "Hematocrit", "Hemoglobin", "Platelets", "Mean platelet volume ", "Lymphocytes", "Mean corpuscular hemoglobin concentration (MCHC)", "Leukocytes", "Basophils", "Mean corpuscular hemoglobin (MCH)", "Eosinophils", "Mean corpuscular volume (MCV)", "Monocytes", "Red blood cell distribution width (RDW)", "Serum Glucose", "Neutrophils", "Urea", "Proteina C reativa mg/dL", "Creatinine", "Potassium", "Sodium", "Alanine transaminase", "Aspartate transaminase", "Ionized calcium "]
    x = Dataset.matrix[variables]
    x = x.fillna(0)
    y = Dataset.matrix["Patient addmited to regular ward (1=yes, 0=no)"]

    clf.fit(x, y)
    results = clf.predict(x)
    print(f"Precisão de {accuracy_score(y, results)}\n")

    columns_relevance = pd.DataFrame({"Variavel": list(x.columns), "Importancia": clf.feature_importances_})
    columns_relevance.sort_values("Importancia", ascending = False)
    print(columns_relevance.head(10))

def SemiIntensiveUnit():

    print("\n--------------------------------\n\n>> PACIENTES EM UNIDADES DE TRATAMENTO SEMI-INTENSIVAS:\n")
    print(Dataset.matrix["Patient addmited to semi-intensive unit (1=yes, 0=no)"].value_counts())
    print()

    clf = RandomForestClassifier(n_estimators = 100)

    Dataset.matrix["CovidBinario"] = Dataset.matrix["SARS-Cov-2 exam result"].map(covid_binary)

    variables = ["Patient age quantile", "CovidBinario", "Patient addmited to regular ward (1=yes, 0=no)", "Patient addmited to intensive care unit (1=yes, 0=no)", "Hematocrit", "Hemoglobin", "Platelets", "Mean platelet volume ", "Lymphocytes", "Mean corpuscular hemoglobin concentration (MCHC)", "Leukocytes", "Basophils", "Mean corpuscular hemoglobin (MCH)", "Eosinophils", "Mean corpuscular volume (MCV)", "Monocytes", "Red blood cell distribution width (RDW)", "Serum Glucose", "Neutrophils", "Urea", "Proteina C reativa mg/dL", "Creatinine", "Potassium", "Sodium", "Alanine transaminase", "Aspartate transaminase", "Ionized calcium "]
    x = Dataset.matrix[variables]
    x = x.fillna(0)
    y = Dataset.matrix["Patient addmited to semi-intensive unit (1=yes, 0=no)"]

    clf.fit(x, y)
    results = clf.predict(x)
    print(f"Precisão de {accuracy_score(y, results)}\n")

    columns_relevance = pd.DataFrame({"Variavel": list(x.columns), "Importancia": clf.feature_importances_})
    columns_relevance.sort_values("Importancia", ascending = False)
    print(columns_relevance.head(10))

def IntensiveCareUnit():

    print("\n--------------------------------\n\n>> PACIENTES EM UNIDADES DE TRATAMENTO INTENSIVAS:\n")
    print(Dataset.matrix["Patient addmited to intensive care unit (1=yes, 0=no)"].value_counts())
    print()

    clf = RandomForestClassifier(n_estimators = 100)

    Dataset.matrix["CovidBinario"] = Dataset.matrix["SARS-Cov-2 exam result"].map(covid_binary)

    variables = ["Patient age quantile", "CovidBinario", "Patient addmited to semi-intensive unit (1=yes, 0=no)", "Patient addmited to regular ward (1=yes, 0=no)", "Hematocrit", "Hemoglobin", "Platelets", "Mean platelet volume ", "Lymphocytes", "Mean corpuscular hemoglobin concentration (MCHC)", "Leukocytes", "Basophils", "Mean corpuscular hemoglobin (MCH)", "Eosinophils", "Mean corpuscular volume (MCV)", "Monocytes", "Red blood cell distribution width (RDW)", "Serum Glucose", "Neutrophils", "Urea", "Proteina C reativa mg/dL", "Creatinine", "Potassium", "Sodium", "Alanine transaminase", "Aspartate transaminase", "Ionized calcium "]
    x = Dataset.matrix[variables]
    x = x.fillna(0)
    y = Dataset.matrix["Patient addmited to intensive care unit (1=yes, 0=no)"]

    clf.fit(x, y)
    results = clf.predict(x)
    print(f"Precisão de {accuracy_score(y, results)}\n")

    columns_relevance = pd.DataFrame({"Variavel": list(x.columns), "Importancia": clf.feature_importances_})
    columns_relevance.sort_values("Importancia", ascending = False)
    print(columns_relevance.head(10))

    print("\n--------------------------------")

# def Home():

#     Dataset.matrix["HomeTreatment"] = Dataset.matrix["Patient addmited to regular ward (1=yes, 0=no)", "Patient addmited to semi-intensive unit (1=yes, 0=no)", "Patient addmited to intensive care unit (1=yes, 0=no)"].map(home_treatment)

#     print("\n>> Pacientes tratados em casa:\n")
#     print(Dataset.matrix["HomeTreatment"].value_counts())
#     print()

#     clf = RandomForestClassifier(n_estimators = 100)

#     Dataset.matrix["CovidBinario"] = Dataset.matrix["SARS-Cov-2 exam result"].map(covid_binary)

#     variables = ["Patient age quantile", "CovidBinario", "Patient addmited to semi-intensive unit (1=yes, 0=no)", "Patient addmited to intensive care unit (1=yes, 0=no)", "Hematocrit", "Hemoglobin", "Platelets", "Mean platelet volume ", "Lymphocytes", "Mean corpuscular hemoglobin concentration (MCHC)", "Leukocytes", "Basophils", "Mean corpuscular hemoglobin (MCH)", "Eosinophils", "Mean corpuscular volume (MCV)", "Monocytes", "Red blood cell distribution width (RDW)", "Serum Glucose", "Neutrophils", "Urea", "Proteina C reativa mg/dL", "Creatinine", "Potassium", "Sodium", "Alanine transaminase", "Aspartate transaminase", "Ionized calcium "]
#     x = Dataset.matrix[variables]
#     x = x.fillna(0)
#     y = Dataset.matrix["Patient addmited to regular ward (1=yes, 0=no)"]

#     clf.fit(x, y)
#     results = clf.predict(x)
#     print(f"Precisão de {accuracy_score(y, results)}")

#     columns_relevance = pd.DataFrame({"Variavel": list(x.columns), "Importancia": clf.feature_importances_})
#     columns_relevance.sort_values("Importancia", ascending = False)
#     print(columns_relevance.head(10))
