package JFrame;

import javax.swing.*;
import java.awt.*;

public class Example01 extends JFrame {
    public void CreateJFrame(String title){
        JFrame jFrame=new JFrame(title);
        Container container=jFrame.getContentPane();
        JLabel jLabel=new JLabel("JFrame 窗体");
        jLabel.setHorizontalAlignment(SwingConstants.CENTER);
        container.add(jLabel);
        container.setBackground(Color.CYAN);
        jFrame.setVisible(true);
        jFrame.setSize(500,550);
        jFrame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

    }

    public static void main(String[] args) {
        new Example01().CreateJFrame("第一个窗体");
    }
}