import React, { useState, useEffect } from 'react';
import { initializeApp } from 'firebase/app';
import { getDatabase, ref, onValue, push, set } from 'firebase/database';
import axios from 'axios';
import './App.css'; // Import the CSS file

const firebaseConfig = {
  apiKey: "AIzaSyB7xzN9xLaINlMB6f-A48vMTdAVshjyGN0",
  authDomain: "smart-otp-lock-system.firebaseapp.com",
  databaseURL: "https://smart-otp-lock-system-default-rtdb.firebaseio.com",
  projectId: "smart-otp-lock-system",
  storageBucket: "smart-otp-lock-system.appspot.com",
  messagingSenderId: "331568497817",
  appId: "1:331568497817:web:81c99e99f2e4acdb7ae408",
  measurementId: "G-EED3CJ8TEB",
};

const app = initializeApp(firebaseConfig);
const database = getDatabase(app);

const PasswordsScreen = () => {
  const [passwords, setPasswords] = useState([]);
  const [phoneNumber, setPhoneNumber] = useState('');

  useEffect(() => {
    fetchPasswords();
  }, []);

  const fetchPasswords = () => {
    try {
      const passwordsRef = ref(database, 'passwords');
      onValue(passwordsRef, (snapshot) => {
        const data = snapshot.val();
        if (data) {
          const passwordList = Object.entries(data).map(([key, value]) => ({
            id: key,
            phoneNumber: value.phoneNumber,
            password: value.password,
          }));
          setPasswords(passwordList);
        }
      });
    } catch (error) {
      console.log('Error fetching passwords:', error);
    }
  };

  const handleAddPassword = async () => {
    try {
      if (!phoneNumber) {
        console.log('Please enter a phone number');
        return;
      }

      const password = generateRandomPassword();
      try {
        // ... existing code ...
    
        await axios.post('http://localhost:3000/api/send-sms', { phoneNumber, password });

    
        // ... remaining code ...
      } catch (error) {
        console.log('Error adding password:', error);
      }
      const passwordsRef = ref(database, 'passwords');
      const newRef = push(passwordsRef);
      const newKey = newRef.key;
      await set(newRef, { phoneNumber, password });
      fetchPasswords();
      setPhoneNumber('');
    } catch (error) {
      console.log('Error adding password:', error);
    }
  };

  const generateRandomPassword = () => {
    const randomPassword = Math.floor(10000 + Math.random() * 90000);
    return String(randomPassword);
  };

  const handleDeletePassword = async (id) => {
    try {
      const passwordRef = ref(database, `passwords/${id}`);
      await set(passwordRef, null);
      fetchPasswords();
    } catch (error) {
      console.log('Error deleting password:', error);
    }
  };

  const renderItem = ({ item }) => (
    <div className="passwordItem">
      <p className="itemText">Phone Number: {item.phoneNumber}</p>
      <p className="itemText">Password: {item.password}</p>
      <button className="deleteButton" onClick={() => handleDeletePassword(item.id)}>
        Delete
      </button>
    </div>
  );

  return (
    <div className="container">
      <div className="contentContainer">
        <input
          className="input"
          type="text"
          placeholder="Enter Phone Number"
          value={phoneNumber}
          onChange={(e) => setPhoneNumber(e.target.value)}
        />
        <button className="button" onClick={handleAddPassword}>
          Add Password
        </button>
      </div>
      <ul className="passwordList">
        {passwords.map((item) => (
          <li key={item.id}>{renderItem({ item })}</li>
        ))}
      </ul>
    </div>
  );
};

export default PasswordsScreen;