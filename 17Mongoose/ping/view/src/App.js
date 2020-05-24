import React from 'react';
import logo from './logo.svg';
import './App.css';

import Table from './components/Table';
import SearchBar from './components/SearchBar';


class App extends React.Component {
  constructor(props) {
    super(props)
    this.state = {key: '', rows: null } // key: multicast ip, rows: Array where each element is a pair (ip, time(ms))
  }

  __passInfo() {
    fetch('http://localhost:8000/search', // make sure it matches with the C server
      {
        method: 'POST',
        body: this.state.key
        // body: JSON.stringify(this.state), // this.state.key
      }).then(res => {
        return res.json()
      }).then(res => {
        console.log(res)
        let rows = []
        for (let i = 0; i < res.ipList.length; ++i) 
          rows.push({first: res.ipList[i], second: res.timeList[i]})
        this.setState({key: this.state.key, rows: rows})
      }, err => {
        console.log(err)
      })
  }

  handleKeyPress = event => {
    let code = event.keyCode || event.which;
    if (code === 13) {  // enter pressed
      this.__passInfo()
      console.log(this.state)
    }
  }

  handleOnChange = (event) => {
    this.setState({ // after calling setState the render method will be invocated
      key: event.target.value})
    console.log(this.state);
  }

  // to comunicate these two components I passes a callback so that the child pass me information, with this I passed it to the other child
  render() {
    let table = <div/>
    if (this.state.rows !== null) // display the table until something is searched
      table = <Table rows={this.state.rows} />
    return (
      <div>
        <div className="App">
          <header className="App-header">
            <img src={logo} className="App-logo" alt="logo" />
          </header>
        </div>
        <SearchBar 
          handleOnKeyPress={this.handleKeyPress} 
          handleOnChange={this.handleOnChange} 
          />
        { table }
      </div>
    );
  }
}


export default App;