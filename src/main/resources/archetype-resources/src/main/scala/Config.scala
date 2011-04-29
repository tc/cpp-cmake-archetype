package ${package}

import org.yaml.snakeyaml.Yaml
import org.slf4j.Logger
import org.slf4j.LoggerFactory
import java.io.InputStream
import java.io.FileInputStream
import java.io.File

import javax.sql.DataSource
import com.mysql.jdbc.jdbc2.optional._
import scala.collection.JavaConversions._

object Config{
  val environment = if(System.getenv("APP_ENV") != null) System.getenv("APP_ENV") else "development"

  def getMySqlDataSource(dbName:String):DataSource = {
    val dbSettings = getDatabaseSettings(dbName)

    val serverName = dbSettings.getOrElse("host", "localhost").asInstanceOf[String]
    val port = dbSettings.getOrElse("port", 3306).asInstanceOf[Int]
    val databaseName = dbSettings.get("database").asInstanceOf[String]
    val user = dbSettings.getOrElse("username", "root").asInstanceOf[String]
    val password = dbSettings.get("password").asInstanceOf[String]

    val dataSource = new MysqlConnectionPoolDataSource()
    dataSource.setUser(user)
    dataSource.setPassword(password)
    dataSource.setUrl("jdbc:mysql://%s:%d/%s?useUnicode=true&characterEncoding=UTF-8&autoReconnect=true".format(serverName, port, databaseName))
    dataSource.setEncoding("UTF-8")
    dataSource
  }

  def getDatabaseSettings(dbName:String):java.util.HashMap[String,Any] = {
    LoggerFactory.getLogger(getClass.toString).info("Using %s environment for database: %s".format(environment, dbName))

    val dbSettingFilename = "src/main/resources/config/db/" + dbName + ".yml"
    readYamlSettings(dbSettingFilename)
  }

  def readYamlSettings(filename:String):java.util.HashMap[String,Any] = {
    val stream = new FileInputStream(new File(filename))
    val dbYaml = new Yaml
    val env = dbYaml.load(stream).asInstanceOf[java.util.HashMap[String,Any]]
    val settings = env.get(environment).asInstanceOf[java.util.HashMap[String,Any]]
    stream.close

    settings
  }
}

