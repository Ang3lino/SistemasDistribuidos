
import React from 'react';

class Table extends React.Component {
    constructor(props) {
      super(props);
      fetch('http://localhost:8000/search')
        .then(res => {
          return res.json()
        }).then(res => {
          console.log(res)
        }, err => {
          console.log(err)
        })
    }

    componentDidMount() {
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
                    <tr>
                        <td>214.4315.5344</td>
                        <td>cinco mil</td>
                    </tr>
                    </tbody>
                </table>
            </div>
        );
    }

}

export default Table;