package org.lichsword.game.ui.panel;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Graphics;

import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;

public class DrawTriangle extends JPanel {
    /**
     * 
     */
    private static final long serialVersionUID = -2833633205974872757L;

    /**
     * 
     */
    public DrawTriangle() {
        super();
        initContentView();
    }

    private void initContentView() {
        setBorder(new EmptyBorder(5, 5, 5, 5));
        setLayout(new BorderLayout(0, 0));
    }

    @Override
    public void paint(Graphics graphics) {
        graphics.setColor(new Color(255, 0, 0));
        graphics.drawLine(50, 100, 80, 100);
        graphics.drawLine(80, 100, 120, 120);
        graphics.drawLine(120, 120, 50, 100);
    }
}
