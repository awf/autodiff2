import scala.io.Source

object ExtractCSV {
  val TIME = "time per call = "
  var currentType: String = _
  var currentMet: String = _
  def main(args: Array[String]): Unit = {
    val FILE = args(0)
    val lines = Source.fromFile(FILE).getLines.toList
    
    def isTime(s: String) = s.contains(TIME)
    def isExe(s: String) = s.contains(".exe") || s.contains("python")
    val data = scala.collection.mutable.HashMap[String, List[(String, Double)]]()
    def extractTime(s: String) = s.substring(s.indexOf(TIME) + TIME.length).dropRight(2).toDouble
    for(i <- lines) { 
      if(isTime(i)) 
        data(currentType) = data(currentType) :+ (currentMet -> extractTime(i)) 
      else if (isExe(i)) 
        currentMet = i 
      else {
        data(i) = Nil 
        currentType = i 
      }
    }
    val dataSeq = data.toSeq.sortBy(_._1)
    val cols = "" :: dataSeq(0)._2.map(_._1)
    val rows = dataSeq.map(x => x._1 :: x._2.map(_._2))
    println(cols.mkString(","))
    println(rows.map(_.mkString(",")).mkString("\n"))
  }
}
