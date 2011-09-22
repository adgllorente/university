/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package switchsimulator;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author kuve
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        String path;
        try {
            System.out.println("Write the path to the network description file");
            path = in.readLine();
            File f = new File(path);

            //Variables
            int rate = 0;
            String name = null;
            int frequency = 0;
            int packetSize = 0;

            //Parsing file
            if (f.exists()) {
                BufferedReader inFile = new BufferedReader(new InputStreamReader(new FileInputStream(f)));
                String line = null;

                //Regex Variables
                String regexTitle = "##.*";
                String regexName = "name:[a-z][a-z]*";
                String regexFrequency = "frequency:[0-9][0-9]*";
                String regexRate = "rate:[0-9][0-9]*";
                String regexPacketSize = "packet_size:[0-9][0-9]*";

                while ((line = inFile.readLine()) != null) {

                    //To lowercase
                    line = line.toLowerCase();
                    line = line.trim();

                    //Parsing data
                    if (!line.matches(regexTitle)) {
                        if (line.matches(regexRate)) {
                            line = line.replaceAll("rate:", "");
                            rate = Integer.parseInt(line);
                        }
                        if (line.matches(regexName)) {
                            line = line.replaceAll("name:", "");
                            name = line;
                        }
                        if (line.matches(regexFrequency)) {
                            line = line.replaceAll("frequency:", "");
                            frequency = Integer.parseInt(line);
                        }
                        if (line.matches(regexPacketSize)) {
                            line = line.replaceAll("packet_size:", "");
                            packetSize = Integer.parseInt(line);
                        }
                    }

                    //Creating object
                    if (rate != 0 && name != null & frequency != 0 && packetSize != 0) {
                        Connection c = new Connection(name, packetSize, frequency, rate);
                        System.out.println("Connection created");

                        //Restarting variables
                        rate = 0;
                        name = null;
                        frequency = 0;
                        packetSize = 0;
                        
                    }
                }
            }
        } catch (IOException ex) {
            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
        }

    }
}
