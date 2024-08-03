#include "nltk.hh"

Nltk &Nltk::getInstance()
{
    static Nltk nltk;
    return nltk;
}

Nltk::Nltk()
{
    if (!Py_IsInitialized())
        Py_Initialize(); // 初始化python解释器
}

Nltk::~Nltk()
{
    // Finalize Python interpreter
    Py_Finalize();
}
std::vector<std::string> Nltk::nltkExtractPhrase(std::string text)
{
    std::vector<std::string> result;
    if (!Py_IsInitialized())
    {
        LogERROR("Python is not initialized!");
        return result;
    }

    const char *script = R"(
import nltk
from nltk.tokenize import word_tokenize, PunktSentenceTokenizer
from nltk import pos_tag
from nltk.chunk import RegexpParser

def extract_phrases(text):

    nltk.data.path.append('./nltk_dict')
    sentence_tokenizer = PunktSentenceTokenizer()
    sentences = sentence_tokenizer.tokenize(text)
    
    grammar = r"""
        NP: {<DT>?<JJ>*<NN>+}
        PP: {<IN><[^.?,:;()]+><[^.?,:;()]+>}
        KK: {<IN><NP>}
        VP: {<VB.*><NP|PP|CLAUSE>+}
        ADVP: {<RB><RB>}
        ADJP: {<JJ><CC><JJ>}
    """
    chunk_parser = RegexpParser(grammar)
    
    phrases = []
    
    for sentence in sentences:
        words = word_tokenize(sentence)
        tagged_words = pos_tag(words)
        chunked = chunk_parser.parse(tagged_words)
        
        for subtree in chunked.subtrees():
            if subtree.label() in ['PP', 'VP', 'ADVP', 'ADJP', 'kk']:
                phrase = " ".join(word for word, tag in subtree.leaves())
                phrases.append(phrase)
    return phrases
)";

    PyRun_SimpleString(script);

    // Get reference to the main module
    PyObject *main_module = PyImport_AddModule("__main__");
    PyObject *main_dict = PyModule_GetDict(main_module);

    // Get reference to the extract_phrases function
    PyObject *extract_phrases_func = PyDict_GetItemString(main_dict, "extract_phrases");

    if (extract_phrases_func && PyCallable_Check(extract_phrases_func))
    {
        // Convert C++ string to Python string
        PyObject *py_text = PyUnicode_FromString(text.c_str());

        // Call the extract_phrases function with the text argument
        PyObject *args = PyTuple_Pack(1, py_text);
        PyObject *py_phrases = PyObject_CallObject(extract_phrases_func, args);
        Py_DECREF(args);
        Py_DECREF(py_text);

        if (py_phrases && PyList_Check(py_phrases))
        {
            // Convert Python list of phrases to C++ vector of strings
            for (Py_ssize_t i = 0; i < PyList_Size(py_phrases); ++i)
            {
                PyObject *py_phrase = PyList_GetItem(py_phrases, i);
                result.push_back(PyUnicode_AsUTF8(py_phrase));
            }
            Py_DECREF(py_phrases);
        }
    }
    return result;
}

#if false
int main()
{
    std::string text = "The King took a heavy chamois leather bag from under his cloak and laid it on the table.\
\"There are three hundred pounds in gold and seven hundred in notes,\" he said. Holmes scribbled a receipt upon a sheet of his note-book and handed it to him.\
But to the generals, especially the foreign ones in the Russian\
army, who wished to distinguish themselves, to astonish somebody,\
and for some reason to capture a king or a duke--it seemed that now-\
when any battle must be horrible and senseless--was the very time to\
fight and conquer somebody. Kutuzov merely shrugged his shoulders when\
one after another they presented projects of maneuvers to be made with\
those soldiers--ill-shod, insufficiently clad, and half starved--who\
within a month and without fighting a battle had dwindled to half\
their number, and who at the best if the flight continued would have\
to go a greater distance than they had already traversed, before\
they reached the frontier. He sat on the comfortable chair. A beautiful, sunny day brightened our spirits. The cat slowly crept under the table.\
So it was at Krasnoe, where they expected to find one of the three\
French columns and stumbled instead on Napoleon himself with sixteen\
thousand men. Despite all Kutuzov's efforts to avoid that ruinous\
encounter and to preserve his troops, the massacre of the broken mob\
of French soldiers by worn-out Russians continued at Krasnoe for three\
days.";
    std::vector<std::string> phrases;

    extract_phrases_with_nltk(text, phrases);

    std::cout << "Extracted Phrases:" << std::endl;
    for (const auto &phrase : phrases)
    {
        std::cout << phrase << std::endl;
    }

    return 0;
}

#endif
