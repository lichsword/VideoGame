package org.lichsword.game.ui.panel;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.event.ComponentEvent;
import java.awt.event.ComponentListener;
import java.util.Random;

import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;

public class SwapBuffer extends JPanel {

    /**
     * 
     */
    private static final long serialVersionUID = -6310015861631896912L;

    /**
     * 
     */
    public SwapBuffer() {
        super();
        initContentView();
        addComponentListener(mGameCanvasListener);
    }

    private Image mBufferImage;

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

        drawBufferImage();
        swapBuffer(graphics);
    }

    private final Random mRandom = new Random(System.currentTimeMillis());

    private void drawBufferImage() {
        Graphics graphics = mBufferImage.getGraphics();
        Color color = new Color(mRandom.nextInt(255), mRandom.nextInt(255),
                mRandom.nextInt(255));
        graphics.setColor(color);
        graphics.fillRect(mRandom.nextInt(100), mRandom.nextInt(100),
                mRandom.nextInt(200), mRandom.nextInt(200));
    }

    private void swapBuffer(Graphics graphics) {
        graphics.drawImage(mBufferImage, 0, 0, dimension.width,
                dimension.height, Color.BLACK, null);
    }

    Dimension dimension;

    GameCanvasListener mGameCanvasListener = new GameCanvasListener();

    class GameCanvasListener implements ComponentListener {

        @Override
        public void componentHidden(ComponentEvent e) {
        }

        @Override
        public void componentMoved(ComponentEvent e) {
        }

        @Override
        public void componentResized(ComponentEvent e) {
            dimension = e.getComponent().getSize();
            mBufferImage = createImage(dimension.width, dimension.height);
        }

        @Override
        public void componentShown(ComponentEvent e) {
        }

    }
}
