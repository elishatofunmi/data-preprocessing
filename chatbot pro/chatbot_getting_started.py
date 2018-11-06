# creating a new chatbot
from chatterbot import ChatBot
chatbot = ChatBot("market soup")

# Training your chatbot
from chatterbot.trainers import ListTrainer

conversation = ['Hello', "hi there!", 'how aare you doing', "I'm doing great.",
                "That is good to hear", "thank you", "you're welcome"]
# getting a response
response = chatbot.get_response("Good morning!")
print reponse

# setting the storage adapter
bot = ChatBot("First bot",storage_adapter = 'chatterbot.storage.SQLStorageAdapter',
              database = './database.sqlite3')


# input and output adapters
# the input adapter simply reads the user's input from the terminal.
# the output terminal adapter prints out the chat bot's response.

bot = ChatBot('First Bot', storage_adapter = 'chatterbot.storage.SQLStorageAdapter',
              input_adapter = 'chatterbot.input.TerminalAdapter',
              output_adapter = 'chatterbot.output.TerminalAdapter',
              database = './database.sqlite3')

# logic_adapters is a list of logic adapters, it is a class that takes an input
# statement and returns a reponse to that statement.
# here we decide to use mathematicalEvaluation adapter to solve math problems that
# uses basic operations.
# Also the timelogicadapter for time.

bot = ChatBot('First Bot', storage_adapter = 'chatterbot.storage.SQOStorageAdapter',
              input_adapter = 'chatterbot.input.TerminalAdapter',
              output_adapter = 'chatterbot.output.TerminalAdapter',
              logic_adapters = ['chatterbot.logic.MathematicalEvaluation',
                                'chatterbot.logic.TimeLogicAdapter'],
              database = './database.sqlite3')

# getting reponse from your chatbot
# keeps waiting for response from the user and breaks out of the loop when
# user enters Ctrl+c.

while True:
    try:
        bot_input = bot.get_response(None)
    except (KeyboardInterrupt, EOFError, SystemExit):
        break

# Training your chatbot, at this point this helps the chatbot to learn as we
# communicate with it, by training it with existing conversations.

bot.train(['How are you?', 'I am good.', "That is good to hear.", "thank you",
           'you are welcome.'])







