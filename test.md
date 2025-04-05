At the end of the day, color is our brain's interpretation of an electromagnetic waves. We only have three types of light sensors in our eyeballs, so our brain basically makes up the color spectrum from combinations of those responses! Not only do our eyeballs use discrete "sensors", but our cameras, monitors, projectors, ect all use different ways of capturing and displaying light! Maintaining any sense of consistency across all of these devices is a huge challenge. Thats where color management software comes in!

Not only do editing programs like Davinci Resolve, Photoshop, and Blender rely on color management, but MANY different devices and industries use these methods.

I created a function I'm proud of (still a lot of testing to do) that calculates difference in color - the CIEDE3000 formula. This method is currently used in many industries for matching color.

I transferred the logic from an academic paper describing the algorithm (Sharma 2005). It is an exercise of naming variables and limiting floating point error. This uses a domain driven design approach! I want the code to reflect the underlying science, and not be bogged down by concepts exclusive to the coding domain.

[Sharma 2005](<https://hajim.rochester.edu/ece/sites/gsharma/ciede2000/ciede2000noteCRNA.pdf>)
[Bruce Lindbloom's Color Difference Calculator](<http://www.brucelindbloom.com/index.html?Eqn_ChromAdapt.html>)
