import React, { useState } from "react";
import Content from "./components/Content";

const ContactPage = () => {
  const [formData, setFormData] = useState({
    name: "",
    email: "",
    message: "",
  });

  const [submitStatus, setSubmitStatus] = useState(null);

  const handleChange = (e) => {
    const { name, value } = e.target;
    setFormData((prevState) => ({
      ...prevState,
      [name]: value,
    }));
  };

  const handleSubmit = (e) => {
    e.preventDefault();
    if (formData.name && formData.email && formData.message) {
      setSubmitStatus("success");
      setFormData({ name: "", email: "", message: "" });
    } else {
      setSubmitStatus("error");
    }
  };

  return (
    <div className="contact-container max-w-4xl mx-auto px-4 py-12">
      <header className="text-center mb-16">
        <h1 className="text-5xl font-bold text-gray-800 mb-4">
          Connect with Stitchify
        </h1>
        <p className="text-xl text-gray-600 max-w-3xl mx-auto">
          We're excited to hear about your ideas, questions, and potential
          collaborations.
        </p>
      </header>

      <Content title="Contact Our Team">
        <div className="contact-content grid md:grid-cols-2 gap-12">
          {}
          <div className="contact-form md:col-span-2">
            <h3 className="text-2xl font-semibold mb-6 text-gray-800">
              Send Us a Message
            </h3>
            <form onSubmit={handleSubmit} className="space-y-4">
              <div>
                <label
                  htmlFor="name"
                  className="block text-sm font-medium text-gray-700 mb-2"
                >
                  Full Name
                </label>
                <input
                  type="text"
                  id="name"
                  name="name"
                  value={formData.name}
                  onChange={handleChange}
                  required
                  className="w-full px-3 py-2 border border-gray-300 rounded-md focus:outline-none focus:ring-2 focus:ring-blue-500"
                />
              </div>
              <div>
                <label
                  htmlFor="email"
                  className="block text-sm font-medium text-gray-700 mb-2"
                >
                  Email Address
                </label>
                <input
                  type="email"
                  id="email"
                  name="email"
                  value={formData.email}
                  onChange={handleChange}
                  required
                  className="w-full px-3 py-2 border border-gray-300 rounded-md focus:outline-none focus:ring-2 focus:ring-blue-500"
                />
              </div>
              <div>
                <label
                  htmlFor="message"
                  className="block text-sm font-medium text-gray-700 mb-2"
                >
                  Your Message
                </label>
                <textarea
                  id="message"
                  name="message"
                  rows="4"
                  value={formData.message}
                  onChange={handleChange}
                  required
                  className="w-full px-3 py-2 border border-gray-300 rounded-md focus:outline-none focus:ring-2 focus:ring-blue-500"
                ></textarea>
              </div>

              {submitStatus === "success" && (
                <div
                  className="bg-green-100 border border-green-400 text-green-700 px-4 py-3 rounded relative"
                  role="alert"
                >
                  Message sent successfully! We'll get back to you soon.
                </div>
              )}

              {submitStatus === "error" && (
                <div
                  className="bg-red-100 border border-red-400 text-red-700 px-4 py-3 rounded relative"
                  role="alert"
                >
                  Please fill out all fields before submitting.
                </div>
              )}

              <button
                type="submit"
                className="w-full bg-blue-600 text-white py-2 rounded-md hover:bg-blue-700 transition-colors"
              >
                Send Message
              </button>
            </form>
          </div>

          {}
          <div className="contact-info md:col-span-2">
            <h3 className="text-2xl font-semibold mb-6 text-gray-800">
              Contact Information
            </h3>
            <div>
              <h4 className="font-medium text-gray-700">Email</h4>
              <a
                href="mailto:wiktoria.rozkosz@epfl.ch"
                className="text-blue-600 hover:underline"
              >
                wiktoria.rozkosz@epfl.ch
              </a>
            </div>
            <div>
              <h4 className="font-medium text-gray-700">Location</h4>
              <p className="text-gray-600">EPFL, Lausanne, Switzerland</p>
            </div>
          </div>
        </div>
      </Content>
    </div>
  );
};

export default ContactPage;
