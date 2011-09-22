import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.sql.Statement;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import persistence.*;

public class Parser {

	/**
	 * @param args
	 */
	Connection con;

	public void Parser() {
	}

	public static void main(String[] args) {
		System.out.println("Write the path to the XML file");
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		String fileName;
		try {
			fileName = in.readLine();
			File f = new File(fileName);
			if(f.exists()){
				Parser parser = new Parser();
				parser.parse(f);
			}else{
				System.out.println("Path incorrect");
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	private void parse(File f) {
		DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
		DocumentBuilder db;
		try {
			Class.forName("com.mysql.jdbc.Driver");
			con = DriverManager.getConnection(
					"jdbc:mysql://87.98.161.140/dim4", "dim4", "adrian1987");
		} catch (Exception e) {
			e.printStackTrace();
		}
		try {
			
			//Removing FK
			PreparedStatement st = this.con.prepareStatement("SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;");
			st.execute();
			st = this.con.prepareStatement("SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;");
			st.execute();
			st = this.con.prepareStatement("SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL';");
			st.execute();
			
			db = dbf.newDocumentBuilder();
			Document doc = db.parse(f);
			
			//Normalize text representation
			doc.getDocumentElement().normalize();
			
			//Getting students
			NodeList nodeStudents = doc.getElementsByTagName("student");
			for(int i=0;i<nodeStudents.getLength();i++){
				
				Node studentNode = nodeStudents.item(i);
				
				//Saving student info
				NamedNodeMap studentAttrs = studentNode.getAttributes();
				int StudentID = Integer.parseInt(studentAttrs.getNamedItem("id").getNodeValue());
				String StudentName = studentAttrs.getNamedItem("name").getNodeValue();
				String StudentSurname = studentAttrs.getNamedItem("surname").getNodeValue();
				String StudentMatriculationID = studentAttrs.getNamedItem("matriculationID").getNodeValue();
				String StudentPassword = studentAttrs.getNamedItem("password").getNodeValue();
				Student s = new Student(StudentID, StudentName, StudentSurname, StudentMatriculationID, StudentPassword);
				s.save(this.con);
				System.out.println("Added student:\t" + s.toString());
				
				//Getting courses
				NodeList coursesNode = ((Element)studentNode).getElementsByTagName("course");
				for(int j=0;j<coursesNode.getLength();j++){
					
					Node courseNode = coursesNode.item(j);
					
					//Saving course information
					NamedNodeMap courseAttrs = courseNode.getAttributes();
					int CourseID = Integer.parseInt(courseAttrs.getNamedItem("id").getNodeValue());
					String CourseName = courseAttrs.getNamedItem("name").getNodeValue();
					Course c = new Course(CourseID, CourseName);
					c.save(this.con);
					System.out.println("Added course:\t" + c.toString());
					
					//Getting questionaires
					NodeList questionairesNode = ((Element)courseNode).getElementsByTagName("questionaire");
					for(int k=0;k<questionairesNode.getLength();k++){
						
						Node questionaireNode = questionairesNode.item(k);
						
						//Saving course information
						NamedNodeMap questionaireAttrs = questionaireNode.getAttributes();
						int QuestionaireID = Integer.parseInt(questionaireAttrs.getNamedItem("id").getNodeValue());
						String QuestionaireName = questionaireAttrs.getNamedItem("name").getNodeValue();
						int QuestionaireCourse = Integer.parseInt(questionaireAttrs.getNamedItem("courseID").getNodeValue());
						int QuestionaireStudent = Integer.parseInt(questionaireAttrs.getNamedItem("studentID").getNodeValue());
						Questionaire qs = new Questionaire(QuestionaireID, QuestionaireName, QuestionaireCourse, QuestionaireStudent);
						qs.save(this.con);
						System.out.println("Added questionaire:\t" + qs.toString());
						
						//Getting questions
						NodeList questionsNode = ((Element)questionaireNode).getElementsByTagName("question");
						for(int l=0;l<questionsNode.getLength();l++){
							
							Node questionNode = questionsNode.item(l);
							
							//Saving course information
							NamedNodeMap questionAttrs = questionNode.getAttributes();
							int QuestionID = Integer.parseInt(questionAttrs.getNamedItem("id").getNodeValue());
							String QuestionContent = questionAttrs.getNamedItem("content").getNodeValue();
							String QuestionQuestionaire = questionAttrs.getNamedItem("questionaireID").getNodeValue();
							Question q = new Question(QuestionContent, QuestionID, QuestionQuestionaire);
							q.save(this.con);
							System.out.println("Added question:\t" + q.toString());
							
							//Getting choices
							NodeList choicesNode = ((Element)questionNode).getElementsByTagName("choice");
							for(int m=0;m<choicesNode.getLength();m++){
								
								Node choiceNode = choicesNode.item(m);
								
								//Saving choice information
								NamedNodeMap choiceAttrs = choiceNode.getAttributes();
								int ChoiceID = Integer.parseInt(choiceAttrs.getNamedItem("id").getNodeValue());
								String ChoiceContent = choiceAttrs.getNamedItem("content").getNodeValue();
								int ChoiceQuestion = Integer.parseInt(choiceAttrs.getNamedItem("questionID").getNodeValue());
								int ChoiceCorrect = Integer.parseInt(choiceAttrs.getNamedItem("correct").getNodeValue());
								
								Choice ch = new Choice(ChoiceID, ChoiceContent, ChoiceQuestion, ChoiceCorrect);
								ch.save(this.con);
								System.out.println("Added choice:\t" + ch.toString());
							}
						}
					}
				}
				
				//Getting answers
				NodeList answersNode = ((Element)studentNode).getElementsByTagName("answer");
				for(int n=0;n<answersNode.getLength();n++){
					
					Node answerNode = answersNode.item(n);
					
					//Saving course information
					NamedNodeMap answerAttrs = answerNode.getAttributes();
					int AnswerID = Integer.parseInt(answerAttrs.getNamedItem("id").getNodeValue());
					int AnswerStudent = Integer.parseInt(answerAttrs.getNamedItem("studentID").getNodeValue());
					int AnswerQuestionaire = Integer.parseInt(answerAttrs.getNamedItem("questionaireID").getNodeValue());
					int AnswerQuestion = Integer.parseInt(answerAttrs.getNamedItem("questionID").getNodeValue());
					int AnswerChoice = Integer.parseInt(answerAttrs.getNamedItem("choiceID").getNodeValue());
					Answer a = new Answer(AnswerID, AnswerStudent, AnswerQuestionaire, AnswerQuestion, AnswerChoice);
					a.save(this.con);
					System.out.println("Added answer:\t" + a.toString());
				}
			}
			
			st = this.con.prepareStatement("SET SQL_MODE=@OLD_SQL_MODE;");
			st.execute();
			st = this.con.prepareStatement("SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;");
			st.execute();
			st = this.con.prepareStatement("SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;");
			st.execute();
			
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		try {
			con.close();
		} catch (SQLException e) {
			e.printStackTrace();
		}

	}
}
