from pymongo import MongoClient
from bson.objectid import ObjectId

class AnimalShelter(object):
    """
    CRUD operations for Animal collection in MongoDB.
    """
    
    def __init__(self, USER=None, PASS=None):
        """
        Initializes the connection to MongoDB using aacuser credentials.
        HOST and PORT were retrieved using terminal echo commands.
        """
        
        # The following commented out code is existent from previous assignments.
        # Connection Variables
        #USER = 'aacuser' # Commented these two variables out for Module 5 but kept to maintain old assignment code.
        #PASS = 'SNHU1234'
        
        #HOST = 'nv-desktop-services.apporto.com'
        #PORT = 33329
        HOST = 'localhost'
        PORT = 27017
        DB = 'AAC'
        COL = 'animals'
        
        # Initialize Connection
        #self.client = MongoClient(f'mongodb://{USER}:{PASS}@{HOST}:{PORT}')
        self.client = MongoClient(f'mongodb://{HOST}:{PORT}')
        self.database = self.client[DB]
        self.collection = self.database[COL]
    
    
    def create(self, data):
        """
        Inserts a new document into the collection.
        
        Parameters:
            data (dict): A dictionary representing the document to be inserted.
            
        Returns:
            bool: True if the document was inserted successfully, False otherwise.
        """
        
        if data is not None and isinstance(data, dict):
            try:
                self.database.animals.insert_one(data)
                return True
            except Exception as e:
                print(f'Insert failed: {e}')
                return False
        else:
            print('Insert failed: data must be a non-empty dictionary.')
            return False
    
    
    def read(self, query):
        """
        Finds documents in the animals collection that match the query.
        
        Parameters:
            query (dict): A dictionary representing the filter query.
            
        Returns:
            list: A list of matching documents, or an empty list if none found or error occurs.
        """
        
        if query is not None and isinstance(query, dict):
            try:
                result = self.database.animals.find(query)
                return list(result)
            except Exception as e:
                print(f'Read failed: {e}')
                return []
        else:
            print('Read failed: query must be a non-empty dictionary.')
            return []
    
    
    def update(self, query, values):
        """
        Updates documents in the animals collection that match the query.
        
        Parameters:
            query (dict): A dictionary representing the filter query.
            values (dict): A dictionary of the fields to update using $set
            
        Returns:
            int: The number of documents modified.
        """
        
        if query is not None and isinstance(query, dict) and isinstance(values, dict):
            try:
                result = self.database.animals.update_many(query, {"$set": values})
                return result.modified_count
            except Exception as e:
                print(f'Failed to update: {e}')
                return 0
        else:
            print('Update failed: ensure query and values are dictionaries.')
    
    
    def delete(self, query):
        """
        Deletes documents in the animals collection that match the query.
        
        Parameters:
            query (dict): A dictionary representing the filter query.
            
        Returns:
            int: The number of documents deleted.
        """
        
        if query is not None and isinstance(query, dict):
            try:
                result = self.database.animals.delete_many(query)
                return result.deleted_count
            except Exception as e:
                print(f'Failed to delete: {e}')
                return 0
        else:
            print('Deleted failed: query must be a non-empty dictionary.')
            return 0