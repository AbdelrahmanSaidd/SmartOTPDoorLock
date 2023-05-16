const express = require('express');
const app = express();
const twilio = require('twilio');
const cors = require('cors');

const accountSid = 'ACa2fed3e452e52570724aa5da29f7e5ad';
const authToken = 'e8e0da5099f2ec42fda16c90a7f39671';
const client = twilio(accountSid, authToken);

app.use(express.json());
app.use(cors());
app.post('/api/send-sms', (req, res) => {
  const { phoneNumber, password } = req.body;

  client.messages
    .create({
      body: `Your password is: ${password}`,
      from: '+13022166387',
      to: phoneNumber,
    })
    .then(() => {
      res.status(200).json({ message: 'SMS sent successfully.' });
    })
    .catch(error => {
      console.error('Error sending SMS:', error);
      res.status(500).json({ error: 'Failed to send SMS.' });
    });
});

app.listen(3000, () => {
  console.log('Server running on port 3000');
});


