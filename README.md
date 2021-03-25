# Embedded JSON

By defining a network protocol as containing a section for data that is a predictable distance from the beginning and end
of the embedded json (eson) object, users are free to send anything they like across the network so long as the recepient 
is able to decode it.  

Through this technique, we may encode multiple files in a single eson object simply by marking their size and having some
predictable start point.  

## Files

* pretty.eson
An eson document with formatting that is easier to visualize.  Note that the formatting does not exist in true eson documents, which look like the following file.

* eson.bkup
An example eson document that ends before the data should be inserted for file(s) being embedded.

* example.eson
An actual eson object with an image file embedded within it.
