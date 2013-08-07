package org.lichsword.game.ui.panel;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Graphics;

import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;

public class DrawLinePanel extends JPanel {

    /**
     * 
     */
    private static final long serialVersionUID = 1L;

    /**
     * 
     */
    public DrawLinePanel() {
        super();
        setBorder(new EmptyBorder(5, 5, 5, 5));
        setLayout(null);
        initContentView();
    }

    private void initContentView() {
        setBorder(new EmptyBorder(5, 5, 5, 5));
        setLayout(new BorderLayout(0, 0));
    }

    @Override
    public void paint(Graphics graphics) {
        graphics.setColor(new Color(255, 0, 0));
        graphics.draw3DRect(0, 0, 100, 50, true);
        graphics.setColor(new Color(255, 0, 0));
        graphics.drawLine(0, 0, 100, 50);
        graphics.drawLine(0, 50, 100, 0);
    }
}
