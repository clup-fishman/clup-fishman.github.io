import os
from dotenv import load_dotenv
from pymongo import MongoClient, ASCENDING
from pymongo.errors import PyMongoError


# Load environment variables from a .env file
load_dotenv()


class AnimalShelter(object):
    """
    CRUD operations for Animal collection in MongoDB.
    """
    
    def __init__(self, USER=None, PASS=None):
        """
        Initialize a MongoDB connection using environment variables when available.
        
        Optional Parameters:
        USER (str): Optional username passed directly into the constructor.
        PASS (str): Optional password passed directly into the constructor.
        
        Environment Variables:
        MONGO_USER
        MONGO_PASS
        MONGO_HOST
        MONGO_PORT
        MONGO_DB
        MONGO_COLLECTION
        """
        
        # Load Configuration from environment variables with defaults
        self.user = USER or os.getenv('MONGO_USER')
        self.password = PASS or os.getenv('MONGO_PASS')
        self.host = os.getenv('MONGO_HOST', 'localhost')
        self.port = int(os.getenv('MONGO_PORT', 27017))
        self.db_name = os.getenv('MONGO_DB', 'AAC')
        self.collection_name = os.getenv('MONGO_COLLECTION', 'animals')
        
        try:
            # Build MongoDB URI
            if self.user and self.password:
                mongo_uri = f'mongodb://{self.user}:{self.password}@{self.host}:{self.port}'
            else:
                mongo_uri = f'mongodb://{self.host}:{self.port}'
                
            # Initialize connection
            self.client = MongoClient(mongo_uri)
            self.database = self.client[self.db_name]
            self.collection = self.database[self.collection_name]
            
        except PyMongoError as e:
            print(f'Database connection failed: {e}')
            self.client = None
            self.database = None
            self.collection = None
    
    
    def create(self, data):
        """
        Inserts a new document into the collection.
        
        Parameters:
            data (dict): A dictionary representing the document to be inserted.
            
        Returns:
            bool: True if the document was inserted successfully, False otherwise.
        """
        
        if self.collection is None:
            print('Insert failed: database connection is not available.')
            return False
        
        if not isinstance(data, dict) or not data:
            print('Insert failed: data must be a non-empty dictionary.')
            return False
        
        try:
            result = self.collection.insert_one(data)
            return result.acknowledged
        
        except PyMongoError as e:
            print(f'Insert failed: {e}')
            return False
    
    
    def read(self, query=None, projection=None):
        """
        Finds documents in the animals collection that match a query.
        
        Parameters:
            query (dict): A MongoDB filter query. Defaults to {} if not provided.
            projection (dict): Optional projection dictionary.
            
        Returns:
            list: A list of matching documents, or an empty list if none found or error occurs.
        """
        
        if self.collection is None:
            print('Read failed: database connection is not available.')
            return []
        
        if query is None:
            query = {}
            
        if not isinstance(query, dict):
            print('Read failed: query must be a dictionary.')
            return []
        
        if projection is not None and not isinstance(projection, dict):
            print('Read failed: projection must be a dictionary.')
            return []
        
        try:
            result = self.collection.find(query, projection)
            return list(result)
        
        except PyMongoError as e:
            print(f'Read failed: {e}')
            return []
    
    
    def update(self, query, values):
        """
        Updates documents in the collection that match the query using $set.
        
        Parameters:
            query (dict): A MongoDB filter query.
            values (dict): A dictionary of fields and values to update.
            
        Returns:
            int: The number of documents modified.
        """
        
        if self.collection is None:
            print('Update failed: database connection is not available.')
            return 0
        
        if not isinstance(query, dict):
            print('Update failed: query must be a dictionary.')
            return 0
    
        if not isinstance(values, dict) or not values:
            print('Update failed: values must be a non-empty dictionary.')
            return 0
        
        try:
            result = self.collection.update_many(query, {'$set': values})
            return result.modified_count
        
        except PyMongoError as e:
            print(f'Update failed: {e}')
            return 0
    
    
    def delete(self, query):
        """
        Deletes documents in the collection that match the query.
        
        Parameters:
            query (dict): A MongoDB filter query.
            
        Returns:
            int: The number of documents deleted.
        """
        
        if self.collection is None:
            print('Delete failed: database connection is not available.')
            return 0
        
        if not isinstance(query, dict):
            print('Delete failed: query must be a dictionary.')
            return 0
        
        try:
            result = self.collection.delete_many(query)
            return result.deleted_count
        
        except PyMongoError as e:
            print(f'Delete failed: {e}')
            return 0
        
    
    def create_indexes(self):
        """
        Create indexes for fields commonly used in dashboard filtering.
        
        Returns:
            list: A list of created index names.
        """
        
        if self.collection is None:
            print('Index creation failed: database connection is not available.')
            return []
        
        try:
            created_indexes = []
            
            created_indexes.append(
                self.collection.create_index([('animal_type', ASCENDING)])
            )
            
            created_indexes.append(
                self.collection.create_index([('sex_upon_outcome', ASCENDING)])
            )
            
            created_indexes.append(
                self.collection.create_index([('age_upon_outcome_in_weeks', ASCENDING)])
            )
            
            created_indexes.append(
                self.collection.create_index([('breed', ASCENDING)])
            )
            
            # Compound index for common filter combos
            created_indexes.append(
                self.collection.create_index([
                    ('animal_type', ASCENDING),
                    ('sex_upon_outcome', ASCENDING),
                    ('age_upon_outcome_in_weeks', ASCENDING),
                    ('breed', ASCENDING)
                ])
            )
            
            return created_indexes
        
        except PyMongoError as e:
            print(f'Index creation failed: {e}')
            return []
        
        
    def aggregate(self, pipeline):
        """
        Run an aggregation pipeline against the collection.
        
        Parameters:
            pipeline (list): A MongoDB aggregation pipeline.
            
        Returns:
            list: Aggregation results as a list, or an empty list on failure.
        """
        
        if self.collection is None:
            print('Aggregation failed: database connection is not available.')
            return []
        
        if not isinstance(pipeline, list) or not pipeline:
            print('Aggregation failed: pipeline must be a non-empty list.')
            return []
        
        try:
            result = self.collection.aggregate(pipeline)
            return list(result)
        
        except PyMongoError as e:
            print(f'Aggregation failed: {e}')
            return []