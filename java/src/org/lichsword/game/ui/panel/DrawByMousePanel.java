package org.lichsword.game.ui.panel;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;

public class DrawByMousePanel extends JPanel {

    /**
     * 
     */
    private static final long serialVersionUID = 1615565920497332744L;

    /**
     * 
     */
    public DrawByMousePanel() {
        super();
        initContentView();
    }

    private void initContentView() {
        setBorder(new EmptyBorder(5, 5, 5, 5));
        setLayout(new BorderLayout(0, 0));

        addMouseListener(new MyMouseListener());
    }

    @Override
    public void paint(Graphics graphics) {
        switch (cursor) {
        case 1:
            graphics.setColor(new Color(0, 0, 0));
            graphics.fillOval(firstPos[0], firstPos[1], 5, 5);
            break;
        case 2:
            graphics.setColor(new Color(0, 0, 0));
            graphics.fillOval(secondPos[0], secondPos[1], 5, 5);
            break;
        case 0:
            graphics.setColor(new Color(0, 0, 0));
            graphics.fillOval(thirdPos[0], thirdPos[1], 5, 5);
            graphics.setColor(new Color(255, 0, 0));
            graphics.drawLine(firstPos[0], firstPos[1], secondPos[0],
                    secondPos[1]);
            graphics.drawLine(secondPos[0], secondPos[1], thirdPos[0],
                    thirdPos[1]);
            graphics.drawLine(thirdPos[0], thirdPos[1], firstPos[0],
                    firstPos[1]);
            break;
        default:
            break;
        }

    }

    int[] firstPos = new int[2];
    int[] secondPos = new int[2];
    int[] thirdPos = new int[2];

    int cursor = 0;

    class MyMouseListener implements MouseListener {

        @Override
        public void mouseClicked(MouseEvent e) {
            int x = e.getX();
            int y = e.getY();

            switch (cursor) {
            case 0:
                firstPos[0] = x;
                firstPos[1] = y;
                cursor++;
                repaint();
                break;
            case 1:
                secondPos[0] = x;
                secondPos[1] = y;
                cursor++;
                repaint();
                break;
            case 2:
                thirdPos[0] = x;
                thirdPos[1] = y;
                cursor = 0;
                repaint();
                break;
            default:
                break;
            }
        }

        @Override
        public void mouseEntered(MouseEvent e) {
        }

        @Override
        public void mouseExited(MouseEvent e) {
        }

        @Override
        public void mousePressed(MouseEvent e) {
        }

        @Override
        public void mouseReleased(MouseEvent e) {
        }

    }
}
