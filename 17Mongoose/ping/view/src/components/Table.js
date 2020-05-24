import React from 'react';


class Table extends React.Component {
  constructor(props) {
    super(props);
  }
  
  renderTable() {
    return this.props.rows.map((row, i) => {
      // most of the time a component should have a key attribute
      return <tr key={i}>
        <td>{row.first}</td>
        <td>{row.second}</td>
      </tr>
    })
  }

  render() {
    return (
      <div>
        <table style={{width: "100%"}}>
          <thead>
            <tr>
              <th>IP</th>
              <th>Time (ms)</th>
            </tr>
          </thead>
          <tbody>
            { this.renderTable() }
          </tbody>
        </table>
    </div>
    );
  }
}


export default Table;