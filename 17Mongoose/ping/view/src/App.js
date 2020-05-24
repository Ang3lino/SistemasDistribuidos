import React from 'react';
import logo from './logo.svg';
import './App.css';

import Table from './components/Table';

function App() {
  return (
    <div>
      <div className="App">
        <header className="App-header">
          <img src={logo} className="App-logo" alt="logo" />
        </header>
        <Table />

      </div>


    </div>
  );
}

export default App;
