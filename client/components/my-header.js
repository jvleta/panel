import {
  html,
  css,
  LitElement,
} from "https://cdn.jsdelivr.net/gh/lit/dist@2/all/lit-all.min.js";

export class MyHeader extends LitElement {
  static styles = css`
    header {
      grid-column: 1 / 4;
      font-size: x-large;
      border-bottom-color: black;
      border-bottom: 2px;
      border-bottom-style: solid;
      padding-top: 20px;
      padding-bottom: 20px;
    }
  `;

  constructor() {
    super();
  }

  render() {
    return html`<header>letalib</header>`;
  }
}
customElements.define("my-header", MyHeader);
