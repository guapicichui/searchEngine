
all:
	g++ -g -o offline OfflineMain.cpp Configuration.cpp DictProducer.cpp DirScanner.cpp HandlePage.cpp HandleXML.cpp logger.cpp nltk.cpp PageLib.cpp SimHashPage.cpp  SplitTool.cpp  tinyxml2.cpp  -Iusr/lib/python3.10 -lpython3.10 -llog4cpp -lpthread
# 清理目标
clean:
	rm -f $(OBJ) $(TARGET)

# 伪目标
.PHONY: all clean
