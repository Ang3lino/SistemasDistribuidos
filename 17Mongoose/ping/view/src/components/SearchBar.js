import React from 'react'
// import './SearchBar.css'


class SearchBar extends React.Component {
  constructor(props) {
      super(props)
  }

  render() {
    return (
      <div >
        <input className="form-control mr-sm-2" type="text" placeholder="Search" 
            aria-label="Search"
            onChange={this.props.handleOnChange} 
            onKeyPress={this.props.handleOnKeyPress}
            />
      </div>
    );
  }
}


export default SearchBar