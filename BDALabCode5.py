from pyspark.sql import SparkSession

# Create Spark session
spark = SparkSession.builder.appName("PySparkRDDExample").getOrCreate()

# Load the dataset into RDD
rdd = spark.sparkContext.textFile("your_dataset.csv")

# Split the data by commas and remove the header
header = rdd.first()
rdd_data = rdd.filter(lambda row: row != header).map(lambda line: line.split(","))

# Show the first few rows
for row in rdd_data.take(5):
    print(row)

# Display basic info (for example, count of rows and columns)
num_rows = rdd_data.count()
num_columns = len(rdd_data.take(1)[0])
print(f"Rows: {num_rows}, Columns: {num_columns}")

# Handling missing values: Drop rows with missing values (assuming missing values are empty strings)
rdd_clean = rdd_data.filter(lambda row: all(field != "" for field in row))

# Handling missing values: Fill missing numerical values with a fixed value (e.g., mean or median)
# Assume the numerical column is at index 2
mean_value = rdd_clean.map(lambda row: float(row[2])).mean()
rdd_filled = rdd_clean.map(lambda row: [mean_value if field == "" and i == 2 else field for i, field in enumerate(row)])

# Handling categorical features: Manual encoding (StringIndexer equivalent)
# Assume the categorical column is at index 3
categories = rdd_filled.map(lambda row: row[3]).distinct().zipWithIndex().collectAsMap()

# Convert categorical values to numerical indexes
rdd_encoded = rdd_filled.map(lambda row: row[:3] + [categories[row[3]]] + row[4:])

# Show encoded rows
for row in rdd_encoded.take(5):
    print(row)

from pyspark.ml.feature import VectorAssembler
from pyspark.ml.classification import DecisionTreeClassifier
from pyspark.sql import Row
from pyspark.ml.linalg import Vectors

# Convert RDD into DataFrame for DecisionTree model (label, features format)
rdd_labeled = rdd_encoded.map(lambda row: Row(label=float(row[0]), features=Vectors.dense([float(x) for x in row[1:]])))

# Convert RDD to DataFrame
df_labeled = spark.createDataFrame(rdd_labeled)

# Split data into training and testing
train_data, test_data = df_labeled.randomSplit([0.8, 0.2], seed=42)

# Initialize Decision Tree Classifier
dt = DecisionTreeClassifier(labelCol='label', featuresCol='features')

# Train the model
dt_model = dt.fit(train_data)

# Make predictions on the test set
predictions = dt_model.transform(test_data)
predictions.select("label", "prediction").show(5)

from pyspark.ml.evaluation import MulticlassClassificationEvaluator

# Accuracy
accuracy_evaluator = MulticlassClassificationEvaluator(labelCol="label", predictionCol="prediction", metricName="accuracy")
accuracy = accuracy_evaluator.evaluate(predictions)
print(f"Accuracy: {accuracy}")

# Precision
precision_evaluator = MulticlassClassificationEvaluator(labelCol="label", predictionCol="prediction", metricName="weightedPrecision")
precision = precision_evaluator.evaluate(predictions)
print(f"Precision: {precision}")

# Recall
recall_evaluator = MulticlassClassificationEvaluator(labelCol="label", predictionCol="prediction", metricName="weightedRecall")
recall = recall_evaluator.evaluate(predictions)
print(f"Recall: {recall}")
