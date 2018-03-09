package gui.dialogs;

import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JSpinner;
import javax.swing.JTextField;

public class DialogEventHandling extends JDialog implements ActionListener{

	private static final long serialVersionUID = 1L;
	
	private JMenuItem addCustomer = new JMenuItem("Add customer");
	
	private JTextField nameField = new JTextField();
	private JSpinner ageSpinner = new JSpinner();
	private JRadioButton femaleButton = new JRadioButton("Female",true);
	private JRadioButton maleButton = new JRadioButton("Male");
	private JCheckBox checkBox = new JCheckBox();
	private JComboBox uniBox = new JComboBox();
	
	private JButton okButton = new JButton("OK");
	private JButton cancelButton = new JButton("Cancel");
	
	public void showDialog() {
    	setTitle("Book Shop (Hazifeladat)");
    	setLocation(100,100);
    	setSize(500,300);
    	
    	JMenuBar menubar = new JMenuBar();

    	JMenu customers = new JMenu("Customer");
    	customers.add(addCustomer);
    	customers.add(new JMenuItem("List customers"));
    	menubar.add(customers);
    	
    	JMenu book = new JMenu("Book");
    	menubar.add(book);
    	
    	JMenu sell = new JMenu("Sell");
    	menubar.add(sell);
    	
    	addCustomer.addActionListener(this);
    	
    	setJMenuBar(menubar);
    	
    	
    	setVisible(true);
	}
	
	public void showAdd() {
		
		setTitle("Add customer");
    	setLocation(200,200);
    	setSize(500,300);
    	
    	JPanel inputPanel = new JPanel();
    	inputPanel.setLayout(new GridLayout(6,2));
    	inputPanel.add(new JLabel("Name"));
    	inputPanel.add(nameField);
    	inputPanel.add(new JLabel("Age"));
        inputPanel.add(ageSpinner);
        inputPanel.add(new JLabel("Gender"));
        JPanel genderPanel = new JPanel();
        genderPanel.setLayout(new BorderLayout());
        genderPanel.add(femaleButton, BorderLayout.WEST);
        genderPanel.add(maleButton, BorderLayout.EAST);
        inputPanel.add(genderPanel);
        inputPanel.add(new JLabel("Grantee"));
        inputPanel.add(checkBox);
        inputPanel.add(new JLabel("Qualification"));
        inputPanel.add(uniBox);
        uniBox.addItem(new ComboItem("University of Szeged", "University of Szeged"));
        uniBox.addItem(new ComboItem("ELTE", "ELTE"));
        uniBox.addItem(new ComboItem("BME", "BME"));
        
        JPanel buttonPanel = new JPanel();
        buttonPanel.setLayout(new FlowLayout(FlowLayout.CENTER));
        buttonPanel.add(okButton);
        okButton.addActionListener(this);
        buttonPanel.add(cancelButton);
        cancelButton.addActionListener(this);
        maleButton.addActionListener(this);
        femaleButton.addActionListener(this);
        
        
        setLayout(new BorderLayout());
        add(inputPanel, BorderLayout.CENTER);
        add(buttonPanel, BorderLayout.SOUTH);
        
        
        setVisible(true);
		
	}
	
	String whatGender(JRadioButton gender) {
		if(gender.isSelected()) {
			return "male";
		}
		return "female";
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if(addCustomer == e.getSource()) {
			new DialogEventHandling().showAdd();
			
		}else if(okButton == e.getSource()) {
			if (nameField.getText().isEmpty()) {
                JOptionPane.showMessageDialog(
                        this,
                        "A nev mezo nem lehet ures",
                        "Hiba",
                        JOptionPane.ERROR_MESSAGE);
                return;
        	}else {
        		Object item = uniBox.getSelectedItem();
        		String value = ((ComboItem)item).getValue();
        		String message = new String();
            	message = 
            			"Name: " + nameField.getText() + "\n" +
            			"Age: " + ageSpinner.getValue() + "\n" +
            			"Gender: "  + whatGender(maleButton) + "\n" +
            			"Check: " + (checkBox.isSelected() ? "be van jelolve" : "nincs bejelolve")+ "\n" +
            			"University: "  + value + "\n";
            	
                JOptionPane.showMessageDialog(
                        this,
                        message,
                        "Adatok",
                        JOptionPane.INFORMATION_MESSAGE);
                
                return;
        	}
		}else if(cancelButton == e.getSource()) {
			String message = new String();
        	message = 
        			"Meg lett nyomva a cancel" + "\n";
            JOptionPane.showMessageDialog(
                    this,
                    message,
                    "Adatok",
                    JOptionPane.INFORMATION_MESSAGE);
            
            return;
    	
		}else if(femaleButton == e.getSource()) {
			femaleButton.setSelected(true);
			maleButton.setSelected(false);
		}else if(maleButton == e.getSource()) {
			femaleButton.setSelected(false);
			maleButton.setSelected(true);
		}
		
		
	}

}
