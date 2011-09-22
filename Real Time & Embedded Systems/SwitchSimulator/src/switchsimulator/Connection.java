/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package switchsimulator;

/**
 *
 * @author kuve
 */
public class Connection {

    /**
     * Parameters
     */
    String name;
    int packetSize;
    int frequency;
    int rate;

    /**
     * Methods
     */
    public Connection(String name, int packetSize, int frequency, int rate) {
        this.name = name;
        this.packetSize = packetSize;
        this.frequency = frequency;
        this.rate = rate;
    }

    
}
