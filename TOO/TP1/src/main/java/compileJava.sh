javac com/franckbarbier/bar_code/*.java
jar -cfm test.jar com/franckbarbier/bar_code/MANIFEST.MF com/franckbarbier/bar_code/*.class
java -jar test.jar
