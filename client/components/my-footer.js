import {
  html,
  css,
  LitElement,
} from "https://cdn.jsdelivr.net/gh/lit/dist@2/all/lit-all.min.js";

export class MyFooter extends LitElement {
  static styles = css`
    footer {
      padding: 2rem;
      text-align: center;
      border-top-color: black;
      border-top: 2px;
      border-top-style: solid;
    }
  `;

  constructor() {
    super();
  }

  render() {
    return html`<footer>&copy; 2022 Jimmy Leta</footer>`;
  }
}
customElements.define("my-footer", MyFooter);
