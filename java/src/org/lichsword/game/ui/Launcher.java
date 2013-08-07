package org.lichsword.game.ui;

import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.Rectangle;
import java.awt.Toolkit;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;

import javax.swing.JFrame;
import javax.swing.JTabbedPane;

import org.lichsword.game.manager.AppVersionManager;
import org.lichsword.game.manager.ConfigManager;
import org.lichsword.game.ui.panel.DrawByMousePanel;
import org.lichsword.game.ui.panel.DrawLinePanel;
import org.lichsword.game.ui.panel.DrawTriangle;

public class Launcher extends JFrame {

    private static final long serialVersionUID = 2515814174441087659L;

    public static void main(String[] args) {
        EventQueue.invokeLater(new Runnable() {
            @Override
            public void run() {
                try {
                    Launcher frame = new Launcher();
                    frame.setVisible(true);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
    }

    /**
     * Create the frame.
     */
    public Launcher() {
        initFrameParam();
        initContentView();
    }

    private void initFrameParam() {
        setTitle(AppVersionManager.getInstance().getAppName());
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setBounds(100, 100, 1200, 1000);

        Toolkit kit = Toolkit.getDefaultToolkit();
        Dimension screenSize = kit.getScreenSize();

        int width = screenSize.width;
        int height = screenSize.height;

        int defaultX = (width - getSize().width) / 2;
        int defaultY = (height - getSize().height) / 2;

        ConfigManager manager = ConfigManager.getInstance();

        setBounds(manager.getWindowX(defaultX), manager.getWindowY(defaultY),
                manager.getWindowWidth(ConfigManager.DEFAULT_WINDOW_WIDTH),
                manager.getWindowHeight(ConfigManager.DEFAULT_WINDOW_HEIGHT));

        setResizable(true);

        addWindowListener(mWindowListener);
    }

    private void initContentView() {
        mTabs = new JTabbedPane(JTabbedPane.TOP);
        getContentPane().add(mTabs);
        initChildTab();
    }

    private final String TAB_NAME_DRAW_LINE = "Draw Line";
    private final String TAB_NAME_DRAW_TRIANGLE = "Draw Triangle";
    private final String TAB_NAME_DRAW_BY_MOUSE = "Draw By Mouse";

    private void initChildTab() {
        mTabs.addTab(TAB_NAME_DRAW_LINE, new DrawLinePanel());
        mTabs.addTab(TAB_NAME_DRAW_TRIANGLE, new DrawTriangle());
        mTabs.addTab(TAB_NAME_DRAW_BY_MOUSE, new DrawByMousePanel());

        int index = ConfigManager.getInstance().getWindowTabIndex(0);
        if (index >= mTabs.getTabCount()) {
            index = 0;
        }// end if
        mTabs.setSelectedIndex(index);
    }

    private final WindowListener mWindowListener = new WindowListener() {

        @Override
        public void windowOpened(WindowEvent e) {

        }

        @Override
        public void windowIconified(WindowEvent e) {

        }

        @Override
        public void windowDeiconified(WindowEvent e) {

        }

        @Override
        public void windowDeactivated(WindowEvent e) {

        }

        @Override
        public void windowClosing(WindowEvent e) {
            writeWindowConfigParam();
        }

        @Override
        public void windowClosed(WindowEvent e) {

        }

        @Override
        public void windowActivated(WindowEvent e) {

        }
    };

    private void writeWindowConfigParam() {
        Rectangle rect = Launcher.this.getBounds();
        ConfigManager manager = ConfigManager.getInstance();
        manager.setWindowX(rect.x);
        manager.setWindowY(rect.y);
        manager.setWindowWidth(rect.width);
        manager.setWindowHeight(rect.height);
    }

    private JTabbedPane mTabs;

}
